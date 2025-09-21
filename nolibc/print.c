#include "private/system.h"
#include "private/write_buffer.h"
#include "public/nlc.h"
#include "public/nlc_file.h"

// ============================
// MARK: Integer to string
// ============================

static uSize UnsignedToString(u64 value, const s8 base, cStr out, const u32 min_width) {
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
	return pos;
}

static uSize IntegerToString(const s64 val, cStr out) {
	if (val < 0) {
		const u64 v = (u64)-val;
		const u64 len = UnsignedToString(v, 10, out + 1, 0);
		out[0] = '-';
		return len + 1;
	}
	return UnsignedToString((u64)val, 10, out, 0);
}

void FloatToString(f64 value, cStr out, u64* outLen, const u32 precision) {
	u64 pos = 0;

	// handle sign
	if (value < 0) {
		out[pos++] = '-';
		value = -value;
	}

	// integer part
	const u64 integerPart = (u64)value;
	const u64 integerPartLen = UnsignedToString(integerPart, 10, out + pos, 0);
	pos += integerPartLen;

	// decimal point
	out[pos++] = '.';

	// fractional part
	f64 frac = value - (f64)integerPart;
	for (u32 i = 0; i < precision; i++) {
		frac *= 10.0;
		const u32 digit = (u32)frac;
		if (digit >= 10) break;
		out[pos++] = (s8)('0' + digit);
		frac -= digit;
	}

	*outLen = pos;
}

// ============================
// MARK: Format
// ============================

static void WriteBufferFmtVar(const cStr fmt, __builtin_va_list ap, WriteBuffer* b) {
	const cStr p = fmt;
	s8 numBuff[64];

	while (*p) {
		if (*p != '%') {
			// find next % or end to batch writes
			const cStr start = p;
			while (*p && *p != '%') p++;
			WriteBufferPuts(b, start, (u64)(p - start));
			continue;
		}
		// handle %
		p++; // skip '%'
		if (*p == '%') {
			WriteBufferPutc(b, '%');
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
			const uPtr fptr = __builtin_va_arg(ap, uPtr);
			const f64 f = *(f64*)fptr;
			u64 len = 0;
			FloatToString(f, numBuff, &len, width == 0 ? 6 : width);
			WriteBufferPuts(b, numBuff, len);
			break;
		}
		case 's': {
			const cStr s = __builtin_va_arg(ap, const cStr);
			if (!s) s = (const cStr)"(null)";
			WriteBufferPuts(b, s, cStrLen(s));
			break;
		}
		case 'd': {
			const s64 v = __builtin_va_arg(ap, s64);
			const u64 len = IntegerToString(v, numBuff);
			WriteBufferPuts(b, numBuff, len);
			break;
		}
		case 'u': {
			const u64 v = __builtin_va_arg(ap, u64);
			const u64 len = UnsignedToString(v, 10, numBuff, width);
			WriteBufferPuts(b, numBuff, len);
			break;
		}
		case 'x': {
			const u64 v = __builtin_va_arg(ap, u64);
			const u64 len = UnsignedToString(v, 16, numBuff, width);
			WriteBufferPuts(b, numBuff, len);
			break;
		}
		case 'c': {
			const sPtr ch = __builtin_va_arg(ap, sPtr);
			WriteBufferPutc(b, (s8)ch);
			break;
		}
		default:
			WriteBufferPutc(b, '%');
			if (*p) WriteBufferPutc(b, *p);
			else WriteBufferPutc(b, '?');
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

void PrintFmtVarFile(const int fd, const cStr fmt, __builtin_va_list va_list) {
	WriteBuffer b = {.len = 0, .fd = fd};
	WriteBufferFmtVar(fmt, va_list, &b);
	WriteBufferFlush(&b);
}

void PrintFmtFile(const int fd, const cStr fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = fd};
	__builtin_va_list ap;
	__builtin_va_start(ap, fmt);
	WriteBufferFmtVar(fmt, ap, &b);
	__builtin_va_end(ap);
	WriteBufferFlush(&b);
}

void PrintFmt(const cStr fmt, ...) {
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

void PrintNewLineFile(const int fd) {
	static s8 NL = '\n';
	SysWrite(fd, (u8*)&NL, 1);
}

void PrintNewLine() {
	PrintNewLineFile(FILE_STDOUT);
}

// ---------------------------
// PRINT
// ---------------------------

void PrintFile(const int fd, const cStr s) {
	PrintFileLen(fd, s, cStrLen(s));
}

void PrintFileLen(const int fd, const cStr s, const uSize len) {
	SysWrite(fd, (u8*)s, len);
}

void Print(const cStr s) {
	PrintFile(FILE_STDOUT, s);
}

void PrintLen(const cStr s, const uSize len) {
	PrintFileLen(FILE_STDOUT, s, len);
}

// ---------------------------
// PRINT LN
// ---------------------------

void PrintLnFile(const int fd, const cStr s) {
	PrintLnFileLen(fd, s, cStrLen(s));
}

void PrintLnFileLen(const int fd, const cStr s, const uSize len) {
	SysWrite(fd, (u8*)s, len);
	PrintNewLine();
}

void PrintLn(const cStr s) {
	PrintLnFile(FILE_STDOUT, s);
}

void PrintLnLen(const cStr s, const uSize len) {
	PrintLnFileLen(FILE_STDOUT, s, len);
}