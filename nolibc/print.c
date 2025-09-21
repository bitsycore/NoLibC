#include "private/system.h"
#include "private/write_buffer.h"
#include "public/nlc_file.h"
#include "public/nlc_format.h"
#include "public/nlc_string.h"

// ============================
// MARK: Print
// ============================

// ---------------------------
// PRINT FMT
// ---------------------------

void FileWriteFmtV(const int fd, const cStr fmt, vaList vlist) {
	WriteBuffer b = {.len = 0, .fd = fd};
	WriteBufferFmtV(&b, fmt, vlist);
	WriteBufferFlush(&b);
}

void FileWriteFmt(const int fd, const cStr fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = fd};
	vaList ap;
	__builtin_va_start(ap, fmt);
	WriteBufferFmtV(&b, fmt, ap);
	__builtin_va_end(ap);
	WriteBufferFlush(&b);
}

void PrintFmt(const cStr fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = FILE_STDOUT};
	vaList va;
	__builtin_va_start(va, fmt);
	WriteBufferFmtV(&b, fmt, va);
	__builtin_va_end(va);
	WriteBufferFlush(&b);
}

void PrintFmtV(const cStr fmt, vaList va) {
	WriteBuffer b = {.len = 0, .fd = FILE_STDOUT};
	WriteBufferFmtV(&b, fmt, va);
	WriteBufferFlush(&b);
}

// ---------------------------
// PRINT NEW LINE
// ---------------------------

void PrintNewLine() {
	static s8 NL = '\n';
	SysWrite(FILE_STDOUT, (u8*)&NL, 1);
}

// ---------------------------
// PRINT
// ---------------------------

void Print(const cStr s) {
	const uSize len = cStrLen(s);
	SysWrite(FILE_STDOUT, (u8*)s, len);
}

void PrintLen(const cStr s, const uSize len) {
	SysWrite(FILE_STDOUT, (u8*)s, len);
}

// ---------------------------
// PRINT LN
// ---------------------------

void PrintLn(const cStr s) {
	const uSize len = cStrLen(s);
	SysWrite(FILE_STDOUT, (u8*)s, len);
	PrintNewLine();
}

void PrintLnLen(const cStr s, const uSize len) {
	SysWrite(FILE_STDOUT, (u8*)s, len);
	PrintNewLine();
}
