#include "priv_syscall.h"

u64 syscall(u64 n, u64 a, u64 b, u64 c, u64 d, u64 e, u64 f) {
	u64 ret;
#if defined(__x86_64__)
	register u64 r10 asm("r10") = d;
	register u64 r8 asm("r8") = e;
	register u64 r9 asm("r9") = f;
	asm volatile (
		"syscall"
		: "=a"(ret)
		: "a"(n), "D"(a), "S"(b), "d"(c), "r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory"
	);
#elif defined(__aarch64__)
	register u64 x8 asm("x8") = n;
	register u64 x0 asm("x0") = a;
	register u64 x1 asm("x1") = b;
	register u64 x2 asm("x2") = c;
	register u64 x3 asm("x3") = d;
	register u64 x4 asm("x4") = e;
	register u64 x5 asm("x5") = f;
	asm volatile(
		"svc #0"
		: "+r"(x0)
		: "r"(x1),"r"(x2),"r"(x3),"r"(x4),"r"(x5),"r"(x8)
		: "memory"
	);
	ret = x0;
#endif
	return ret;
}