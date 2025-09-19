#include "nolibc.h"

#include "priv_syscall.h"

// ============================
// Str
// ============================

u64 strlen(const u8* s) {
	u64 n = 0;
	while (s[n] != '\0') n++;
	return n;
}

// ============================
// Print
// ============================

void fPrintNewLine(const u64 fd) {
	static u8 NL = '\n';
	write(fd, &NL, 1);
}

void printNewLine() {
	fPrintNewLine(STDOUT);
}

// ---------------------------
// NO LN
// ---------------------------

void fPrint2(const u64 fd, const u8* s, const u64 len) {
	write(fd, s, len);
}

void print2(const u8* s, const u64 len) {
	fPrint2(STDOUT, s, len);
}

void fPrint(const u64 fd, const u8* s) {
	fPrint2(fd, s, strlen(s));
}

void print(const u8* s) {
	fPrint(STDOUT, s);
}

// ---------------------------
// LN
// ---------------------------

void fPrintln2(const u64 fd, const u8* s, const u64 len) {
	write(fd, s, len);
	printNewLine();
}

void println2(const u8* s, const u64 len) {
	fPrintln2(STDOUT, s, len);
}

void fPrintln(const u64 fd, const u8* s) {
	fPrintln2(fd, s, strlen(s));
}

void println(const u8* s) {
	fPrintln(STDOUT, s);
}