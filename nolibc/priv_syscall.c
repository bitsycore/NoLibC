#include "priv_syscall.h"

sPtr syscall(
	sPtr n,
	uPtr a,
	uPtr b,
	uPtr c,
	uPtr d,
	uPtr e,
	uPtr f
){
	sPtr ret;

#if defined(__x86_64__)

	register uPtr r10 asm("r10") = d;
	register uPtr r8 asm("r8") = e;
	register uPtr r9 asm("r9") = f;
	asm volatile(
		"syscall"
		: "=a"(ret)
		: "a"(n), "D"(a), "S"(b), "d"(c), "r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory"
	);

#elif defined(__i386__)

	asm volatile(
		"int $0x80"
		: "=a"(ret)
		: "a"(n), "b"(a), "c"(b), "d"(c), "S"(d), "D"(e)
		: "memory"
	);

#elif defined(__aarch64__)

	register uPtr x8 asm("x8") = n;
	register uPtr x0 asm("x0") = a;
	register uPtr x1 asm("x1") = b;
	register uPtr x2 asm("x2") = c;
	register uPtr x3 asm("x3") = d;
	register uPtr x4 asm("x4") = e;
	register uPtr x5 asm("x5") = f;
	asm volatile(
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5), "r"(x8)
		: "memory"
	);
	ret = (sPtr)x0;

#elif defined(__arm__)

	register uPtr r7 asm("r7") = n;
	register sPtr r0 asm("r0") = a;
	register uPtr r1 asm("r1") = b;
	register uPtr r2 asm("r2") = c;
	register uPtr r3 asm("r3") = d;
	register uPtr r4 asm("r4") = e;
	register uPtr r5 asm("r5") = f;
	asm volatile(
		"svc 0"
		: "=r"(r0)
		: "r"(r0), "r"(r1), "r"(r2), "r"(r3), "r"(r4), "r"(r5), "r"(r7)
		: "memory"
	);
	ret = r0;

#else
#error "unsupported arch"
#endif

	return ret;
}

// ============================
// GCC use memset for zero-init
// ============================

void* memset(void* ptr, const int value, uPtr num) {
	unsigned char* p = ptr;
	while (num--) {
		*p++ = (unsigned char)value;
	}
	return ptr;
}

// ============================
// System
// ============================

sPtr write(const u64 fd, const u8* buf, const u64 count) {
	return syscall(SYS_write, (uPtr)fd, (uPtr)buf, (uPtr)count, 0, 0, 0);
}

void exit(const s64 status) {
	syscall(SYS_exit, status, 0, 0, 0, 0, 0);
}

int main();

void _start() {
	const int ret = main();
	exit(ret);
}