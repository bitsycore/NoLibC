#include "nolibc.h"

#include "priv_syscall.h"

// ============================
// FD
// ============================

#define STDIN 0
#define STDOUT 1
#define STDERR 2

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

void fPrint2(const u64 fd, const u8* s, const u64 len) {
	write(fd, s, len);
}

void fPrint(const u64 fd, const u8* s) {
	write(fd, s, strlen(s));
}

void print2(const u8* s, const u64 len) {
	write(STDOUT, s, len);
}

void print(const u8* s) {
	write(STDOUT, s, strlen(s));
}

void fPrintln2(const u64 fd, const u8* s, const u64 len) {
	write(fd, s, len);
	printNewLine();
}

void fPrintln(const u64 fd, const u8* s) {
	write(fd, s, strlen(s));
}

void println2(const u8* s, const u64 len) {
	write(STDOUT, s, len);
	printNewLine();
}

void println(const u8* s) {
	write(STDOUT, s, strlen(s));
	printNewLine();
}