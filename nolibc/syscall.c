#include "private/syscall.h"

sPtr SysCall(
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
  #if defined(__APPLE__)
    /* macOS x86_64: rax = 0x2000000 | n, args in rdi,rsi,rdx,r10,r8,r9 */
    register uPtr r10 asm("r10") = d;
    register uPtr r8  asm("r8")  = e;
    register uPtr r9  asm("r9")  = f;
    register uPtr rax asm("rax") = (0x2000000 | (uPtr)n);
    register uPtr rdi asm("rdi") = a;
    register uPtr rsi asm("rsi") = b;
    register uPtr rdx asm("rdx") = c;
    asm volatile(
      "syscall"
      : "+r"(rax)
      : "r"(rdi), "r"(rsi), "r"(rdx), "r"(r10), "r"(r8), "r"(r9)
      : "rcx", "r11", "memory"
    );
    ret = (sPtr)rax;
  #else
    /* Linux x86_64: rax = n, args in rdi,rsi,rdx,r10,r8,r9 */
    register uPtr r10 asm("r10") = d;
    register uPtr r8  asm("r8")  = e;
    register uPtr r9  asm("r9")  = f;
    asm volatile(
      "syscall"
      : "=a"(ret)
      : "a"(n), "D"(a), "S"(b), "d"(c), "r"(r10), "r"(r8), "r"(r9)
      : "rcx", "r11", "memory"
    );
  #endif

#elif defined(__i386__)
  #if defined(__APPLE__)
    /* macOS i386 (historical): eax = 0x2000000 | n, args in ebx,ecx,edx,esi,edi,ebp */
    register uPtr eax asm("eax") = (0x2000000 | (uPtr)n);
    register uPtr ebx asm("ebx") = a;
    register uPtr ecx asm("ecx") = b;
    register uPtr edx asm("edx") = c;
    register uPtr esi asm("esi") = d;
    register uPtr edi asm("edi") = e;
    register uPtr ebp asm("ebp") = f;
    asm volatile(
      "int $0x80"
      : "+r"(eax)
      : "r"(ebx), "r"(ecx), "r"(edx), "r"(esi), "r"(edi), "r"(ebp)
      : "memory"
    );
    ret = (sPtr)eax;
  #else
    /* Linux i386: eax = n, args in ebx,ecx,edx,esi,edi,ebp */
    asm volatile(
      "int $0x80"
      : "=a"(ret)
      : "a"(n), "b"(a), "c"(b), "d"(c), "S"(d), "D"(e)
      : "memory"
    );
  #endif

#elif defined(__aarch64__)
  #if defined(__APPLE__)
    /* macOS arm64: syscall number in x16 = 0x2000000 | n, args in x0-x5 */
    register uPtr x16 asm("x16") = (0x2000000 | (uPtr)n);
    register uPtr x0  asm("x0")  = a;
    register uPtr x1  asm("x1")  = b;
    register uPtr x2  asm("x2")  = c;
    register uPtr x3  asm("x3")  = d;
    register uPtr x4  asm("x4")  = e;
    register uPtr x5  asm("x5")  = f;
    asm volatile(
      "svc #0"
      : "+r"(x0)
      : "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5), "r"(x16)
      : "memory"
    );
    ret = (sPtr)x0;
  #else
    /* Linux arm64: syscall number in x8, args in x0-x5 */
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
  #endif

#elif defined(__arm__)
  /* Linux 32-bit ARM: syscall number in r7, args in r0-r6 */
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
// System
// ============================

sPtr SysWrite(const u64 fd, const u8* buf, const u64 count) {
	return SysCall(SYS_write, (uPtr)fd, (uPtr)buf, (uPtr)count, 0, 0, 0);
}

void SysExit(const s64 status) {
	SysCall(SYS_exit, status, 0, 0, 0, 0, 0);
}