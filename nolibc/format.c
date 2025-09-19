#include "nolibc.h"
#include "priv_syscall.h"
#include "types.h"

#define OUTBUF_SIZE 8196

typedef struct {
	u8 data[OUTBUF_SIZE];
	u64 len;
	u64 fd;
} OutBuf;

static void buf_flush(OutBuf* b) {
	if (b->len > 0) {
		write(b->fd, b->data, b->len);
		b->len = 0;
	}
}

static void buf_putc(OutBuf* b, const u8 c) {
	if (b->len >= OUTBUF_SIZE) buf_flush(b);
	b->data[b->len++] = c;
}

static void buf_write(OutBuf* b, const u8* s, const u64 n) {
	for (u64 i = 0; i < n; i++) {
		buf_putc(b, s[i]);
	}
}

// ============================
// Integer to string
// ============================

static void utoa_base(u64 value, const u8 base, u8* out, u64* out_len, const u32 min_width) {
	// out must be large enough (at least 32 bytes)
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
			const u8 t = out[i];
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

static void itoa_signed(const s64 val, u8* out, u64* out_len) {
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
// Printf
// ============================

static void buffer_printf(const u8* fmt, __builtin_va_list ap, OutBuf* b) {
	const u8* p = fmt;
	u8 numBuff[64];
	static u8 PERCENT = '%';
	static u8 QUESTION = '?';

	while (*p) {
		if (*p != '%') {
			// find next % or end to batch writes
			const u8* start = p;
			while (*p && *p != '%') p++;
			buf_write(b, start, (u64)(p - start));
			continue;
		}
		// handle %
		p++; // skip '%'
		if (*p == '%') {
			buf_putc(b, PERCENT);
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
			const u8* s = __builtin_va_arg(ap, const u8*);
			if (!s) s = (const u8*)"(null)";
			buf_write(b, s, strlen(s));
			break;
		}
		case 'd': {
			const long long v = __builtin_va_arg(ap, long long);
			u64 len = 0;
			itoa_signed(v, numBuff, &len);
			buf_write(b, numBuff, len);
			break;
		}
		case 'u': {
			const unsigned long long v = __builtin_va_arg(ap, unsigned long long);
			u64 len = 0;
			utoa_base(v, 10, numBuff, &len, width);
			buf_write(b, numBuff, len);
			break;
		}
		case 'x': {
			const unsigned long long v = __builtin_va_arg(ap, unsigned long long);
			u64 len = 0;
			utoa_base(v, 16, numBuff, &len, width);
			buf_write(b, numBuff, len);
			break;
		}
		case 'c': {
			const int ch = __builtin_va_arg(ap, int);
			buf_putc(b, (u8)ch);
			break;
		}
		default:
			buf_putc(b, PERCENT);
			if (*p) buf_putc(b, *p);
			else buf_putc(b, QUESTION);
			break;
		}
		if (*p) p++;
	}
}

// ============================
// MARK: Public
// ============================

// ---------------------------
// NO LN
// ---------------------------

void vfPrintF(const u64 fd, const u8* fmt, __builtin_va_list va_list) {
	OutBuf b = {.len = 0, .fd = fd};
	buffer_printf(fmt, va_list, &b);
	buf_flush(&b);
}

void fPrintF(const u64 fd, const u8* fmt, ...) {
	OutBuf b = {.len = 0, .fd = fd};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	buf_flush(&b);
}

void printF(const u8* fmt, ...) {
	OutBuf b = {.len = 0, .fd = STDOUT};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	buf_flush(&b);
}

// ---------------------------
// LN
// ---------------------------

void vfPrintlnF(const u64 fd, const u8* fmt, __builtin_va_list va_list) {
	OutBuf b = {.len = 0, .fd = fd};
	buffer_printf(fmt, va_list, &b);
	buf_putc(&b, '\n');
	buf_flush(&b);
}

void fPrintlnF(const u64 fd, const u8* fmt, ...) {
	OutBuf b = {.len = 0, .fd = fd};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	buf_putc(&b, '\n');
	buf_flush(&b);
}

void printlnF(const u8* fmt, ...) {
	OutBuf b = {.len = 0, .fd = STDOUT};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	buffer_printf(fmt, ap, &b);
	__builtin_va_end(ap);
	buf_putc(&b, '\n');
	buf_flush(&b);
}