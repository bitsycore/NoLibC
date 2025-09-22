#include "private/system.h"
#include "private/write_buffer.h"
#include "public/nlc_file.h"
#include "public/nlc_string.h"

// ============================
// MARK: Print
// ============================

// ---------------------------
// PRINT FMT
// ---------------------------

void FileWriteFmtV(const int fd, const cStr fmt, VaList argList) {
	WriteBuffer b = {.len = 0, .fd = fd};
	WriteBufferFmtV(&b, fmt, argList);
	WriteBufferFlush(&b);
}

void FileWriteFmt(const int fd, const cStr fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = fd};
	VaList ap;
	VaStart(ap, fmt);
	WriteBufferFmtV(&b, fmt, ap);
	VaEnd(ap);
	WriteBufferFlush(&b);
}

void PrintFmt(const cStr fmt, ...) {
	WriteBuffer b = {.len = 0, .fd = FILE_STDOUT};
	VaList va;
	VaStart(va, fmt);
	WriteBufferFmtV(&b, fmt, va);
	VaEnd(va);
	WriteBufferFlush(&b);
}

void PrintFmtV(const cStr fmt, VaList argList) {
	WriteBuffer b = {.len = 0, .fd = FILE_STDOUT};
	WriteBufferFmtV(&b, fmt, argList);
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
