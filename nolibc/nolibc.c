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
	long n = 0;
	while (s[n] != '\0') n++;
	return n;
}

u64 write(const u64 fd, const u8* buf, const u64 count) {
	return syscall(SYS_write, fd, (u64)buf, count, 0, 0, 0);
}

u64 putsLen(const u8* s, const u64 len) {
	write(STDOUT, s, len);
	return putcLr();
}

u64 puts(const u8* s) {
	return putsLen(s, strlen(s));
}

u64 putcLr() {
	static u8 NL = '\n';
	return write(STDOUT, &NL, 1);
}

// ============================
// System
// ============================

u64 exit(const u64 status) {
	syscall(SYS_exit, status, 0, 0, 0, 0, 0);
	return 0;
}

int main();

void _start() {
	const u64 ret = main();
	exit(ret);
}