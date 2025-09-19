#include "../nolibc.h"
#include "priv_nolibc.h"

#define OUTBUF_SIZE 2048

typedef struct WriteBuffer {
	s8 data[OUTBUF_SIZE];
	u64 len;
	u64 fd;
} WriteBuffer;

// ============================
// MARK: Buffer
// ============================

static void WriteBuffer_flush(WriteBuffer* b) {
	if (b->len > 0) {
		write(b->fd, (u8*)b->data, b->len);
		b->len = 0;
	}
}

static void WriteBuffer_putc(WriteBuffer* b, const s8 c) {
	if (b->len >= OUTBUF_SIZE) WriteBuffer_flush(b);
	b->data[b->len++] = c;
}

static void WriteBuffer_puts(WriteBuffer* b, const s8* s, const u64 n) {
	for (u64 i = 0; i < n; i++) {
		WriteBuffer_putc(b, s[i]);
	}
}

// ============================
// MARK: Integer to string
// ============================

static void utoa_base(u64 value, const s8 base, s8* out, u64* out_len, const u32 min_width) {
	u64 pos = 0;
	if (value == 0) {
		out[pos++] = '0';
	}
	else {
		while (value != 0) {
			const u64 rem = value % base;
			out[pos++] = rem < 10 ? '0' + rem : 'a' + (rem - 10);
			value /= base;
		}
		// reverse
		for (u64 i = 0, j = pos - 1; i < j; ++i, --j) {
			const s8 t = out[i];
			out[i] = out[j];
			out[j] = t;
		}
	}
	// pad if needed
	while (pos < min_width) {
		// shift right by one
		for (u64 i = pos; i > 0; --i) out[i] = out[i - 1];
		out[0] = '0';
		pos++;
	}
	*out_len = pos;
}

static void itoa_signed(const s64 val, s8* out, u64* out_len) {
	if (val < 0) {
		const u64 v = (u64)-val;
		u64 len;
		utoa_base(v, 10, out + 1, &len, 0);
		out[0] = '-';
		*out_len = len + 1;
	}
	else {
		utoa_base((u64)val, 10, out, out_len, 0);
	}
}

// ============================
// MARK: Format
// ============================

static void buffer_printf(const s8* fmt, __builtin_va_list ap, WriteBuffer* b) {
	const s8* p = fmt;
	s8 numBuff[64];

	static s8 PERCENT = '%';
	static s8 QUESTION = '?';

	while (*p) {
		if (*p != '%') {
			// find next % or end to batch writes
			const s8* start = p;
			while (*p && *p != '%') p++;
			WriteBuffer_puts(b, start, (u64)(p - start));
			continue;
		}
		// handle %
		p++; // skip '%'
		if (*p == '%') {
			WriteBuffer_putc(b, PERCENT);
			p++;
			continue;
		}

		// optional width (simple, only decimal digits)
		int width = 0;
		while (*p >= '0' && *p <= '9') {
			width = width * 10 + (*p - '0');
			p++;
		}

		switch (*p) {
		case 's': {
			const s8* s = __builtin_va_arg(ap, const s8*);
			if (!s) s = (const s8*)"(null)";
			WriteBuffer_puts(b, s, strlen(s));
			break;
		}
		case 'd': {
			const long long v = __builtin_va_arg(ap, long long);
			u64 len = 0;
			itoa_signed(v, numBuff, &len);
			WriteBuffer_puts(b, numBuff, len);
			break;
		}
		case 'u': {
			const unsigned long long v = __builtin_va_arg(ap, unsigned long long);
			u64 len = 0;
			utoa_base(v, 10, numBuff, &len, width);
			WriteBuffer_puts(b, numBuff, len);
			break;
		}
		case 'x': {
			const unsigned long long v = __builtin_va_arg(ap, unsigned long long);
			u64 len = 0;
			utoa_base(v, 16, numBuff, &len, width);
			WriteBuffer_puts(b, numBuff, len);
			break;
		}
		case 'c': {
			const int ch = __builtin_va_arg(ap, int);
			WriteBuffer_putc(b, (s8)ch);
			break;
		}
		default:
			WriteBuffer_putc(b, PERCENT);
			if (*p) WriteBuffer_putc(b, *p);
			else WriteBuffer_putc(b, QUESTION);
			break;
		}
		if (*p) p++;
	}
}

// ============================
// MARK: Print
// ============================

// ---------------------------
// PRINT FMT
// ---------------------------

void printFmtVarFile(const u64 fd, const s8* fmt, __builtin_va_list va_list) {
	WriteBuffer b = {.len = 0, .fd = fd};
	buffer_printf(fmt, va_list, &b);
	WriteBuffer_flush(&b);
}

void printFmtFile(const u64 fd, const s8* fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = fd};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	WriteBuffer_flush(&b);
}

void printFmt(const s8* fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = FILE_STDOUT};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	WriteBuffer_flush(&b);
}

// ---------------------------
// PRINT FMT LN
// ---------------------------

void printLnFmtVarFile(const u64 fd, const s8* fmt, __builtin_va_list va_list) {
	WriteBuffer b = {.len = 0, .fd = fd};
	buffer_printf(fmt, va_list, &b);
	WriteBuffer_putc(&b, '\n');
	WriteBuffer_flush(&b);
}

void printLnFmtFile(const u64 fd, const s8* fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = fd};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	WriteBuffer_putc(&b, '\n');
	WriteBuffer_flush(&b);
}

void printLnFmt(const s8* fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = FILE_STDOUT};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	WriteBuffer_putc(&b, '\n');
	WriteBuffer_flush(&b);
}

// ---------------------------
// PRINT NEW LINE
// ---------------------------

void printNewLineFile(const u64 fd) {
	static s8 NL = '\n';
	write(fd, (u8*)&NL, 1);
}

void printNewLine() {
	printNewLineFile(FILE_STDOUT);
}

// ---------------------------
// PRINT
// ---------------------------

void printFile(const u64 fd, const s8* s) {
	printFileLen(fd, s, strlen(s));
}

void printFileLen(const u64 fd, const s8* s, const u64 len) {
	write(fd, (u8*)s, len);
}

void print(const s8* s) {
	printFile(FILE_STDOUT, s);
}

void printLen(const s8* s, const u64 len) {
	printFileLen(FILE_STDOUT, s, len);
}

// ---------------------------
// PRINT LN
// ---------------------------

void printLnFile(const u64 fd, const s8* s) {
	printLnFileLen(fd, s, strlen(s));
}

void printLnFileLen(const u64 fd, const s8* s, const u64 len) {
	write(fd, (u8*)s, len);
	printNewLine();
}

void printLn(const s8* s) {
	printLnFile(FILE_STDOUT, s);
}

void printLnLen(const s8* s, const u64 len) {
	printLnFileLen(FILE_STDOUT, s, len);
}