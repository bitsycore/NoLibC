#include "_syscall.h"
#include "_write_buffer.h"

// ============================
// MARK: Integer to string
// ============================

void UnsignedToString(u64 value, const s8 base, s8* out, u64* out_len, const u32 min_width) {
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

void IntegerToString(const s64 val, s8* out, u64* out_len) {
	if (val < 0) {
		const u64 v = (u64)-val;
		u64 len;
		UnsignedToString(v, 10, out + 1, &len, 0);
		out[0] = '-';
		*out_len = len + 1;
	}
	else {
		UnsignedToString((u64)val, 10, out, out_len, 0);
	}
}

// ============================
// MARK: Format
// ============================

static void WriteBufferFmtVar(const s8* fmt, __builtin_va_list ap, WriteBuffer* b) {
	const s8* p = fmt;
	s8 numBuff[64];

	static s8 PERCENT = '%';
	static s8 QUESTION = '?';

	while (*p) {
		if (*p != '%') {
			// find next % or end to batch writes
			const s8* start = p;
			while (*p && *p != '%') p++;
			WriteBufferPuts(b, start, (u64)(p - start));
			continue;
		}
		// handle %
		p++; // skip '%'
		if (*p == '%') {
			WriteBufferPutc(b, PERCENT);
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
		case 'f': {
			SysExit(55);
			break;
		}
		case 's': {
			const s8* s = __builtin_va_arg(ap, const s8*);
			if (!s) s = (const s8*)"(null)";
			WriteBufferPuts(b, s, StrLen(s));
			break;
		}
		case 'd': {
			const s64 v = __builtin_va_arg(ap, s64);
			u64 len = 0;
			IntegerToString(v, numBuff, &len);
			WriteBufferPuts(b, numBuff, len);
			break;
		}
		case 'u': {
			const u64 v = __builtin_va_arg(ap, u64);
			u64 len = 0;
			UnsignedToString(v, 10, numBuff, &len, width);
			WriteBufferPuts(b, numBuff, len);
			break;
		}
		case 'x': {
			const u64 v = __builtin_va_arg(ap, u64);
			u64 len = 0;
			UnsignedToString(v, 16, numBuff, &len, width);
			WriteBufferPuts(b, numBuff, len);
			break;
		}
		case 'c': {
			const sPtr ch = __builtin_va_arg(ap, sPtr);
			WriteBufferPutc(b, (s8)ch);
			break;
		}
		default:
			WriteBufferPutc(b, PERCENT);
			if (*p) WriteBufferPutc(b, *p);
			else WriteBufferPutc(b, QUESTION);
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

void PrintFmtVarFile(const u64 fd, const s8* fmt, __builtin_va_list va_list) {
	WriteBuffer b = {.len = 0, .fd = fd};
	WriteBufferFmtVar(fmt, va_list, &b);
	WriteBufferFlush(&b);
}

void PrintFmtFile(const u64 fd, const s8* fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = fd};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	WriteBufferFmtVar(fmt, ap, &b);
	__builtin_va_end(ap);
	WriteBufferFlush(&b);
}

void PrintFmt(const s8* fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = FILE_STDOUT};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	WriteBufferFmtVar(fmt, ap, &b);
	__builtin_va_end(ap);
	WriteBufferFlush(&b);
}

// ---------------------------
// PRINT NEW LINE
// ---------------------------

void PrintNewLineFile(const u64 fd) {
	static s8 NL = '\n';
	SysWrite(fd, (u8*)&NL, 1);
}

void PrintNewLine() {
	PrintNewLineFile(FILE_STDOUT);
}

// ---------------------------
// PRINT
// ---------------------------

void PrintFile(const u64 fd, const s8* s) {
	PrintFileLen(fd, s, StrLen(s));
}

void PrintFileLen(const u64 fd, const s8* s, const u64 len) {
	SysWrite(fd, (u8*)s, len);
}

void Print(const s8* s) {
	PrintFile(FILE_STDOUT, s);
}

void PrintLen(const s8* s, const u64 len) {
	PrintFileLen(FILE_STDOUT, s, len);
}

// ---------------------------
// PRINT LN
// ---------------------------

void PrintLnFile(const u64 fd, const s8* s) {
	PrintLnFileLen(fd, s, StrLen(s));
}

void PrintLnFileLen(const u64 fd, const s8* s, const u64 len) {
	SysWrite(fd, (u8*)s, len);
	PrintNewLine();
}

void PrintLn(const s8* s) {
	PrintLnFile(FILE_STDOUT, s);
}

void PrintLnLen(const s8* s, const u64 len) {
	PrintLnFileLen(FILE_STDOUT, s, len);
}