#include "private/entry.h"

#include "private/system.h"
#include "public/nlc_system.h"

#define XSTR(x) STR(x)
#define STR(x) #x

NLC_ATTR_USED volatile uSize gArgc;
NLC_ATTR_USED volatile cStr* gArgv;
NLC_ATTR_USED volatile cStr* gEnvp;
NLC_ATTR_USED volatile uPtr* gAuxv;

extern int main(int argc, char** argv);

NLC_ATTR_USED
void StartC(long argc, char** argv) {
	argc = (long)gArgc;
	argv = (cStr*)gArgv;
#if defined(__APPLE__)
	// TODO: macOS auxv ?
#elif defined(__linux__)
	cStr* envp = (cStr*)gEnvp;
	while (*envp) envp++;
	gAuxv = (uPtr*)(envp + 1);
#endif
	const int status = main((int)argc, argv);
	SysExit(status);
}

NLC_ATTR_NAKED
void _start() { // NOLINT(*-reserved-identifier)
#if defined(__APPLE__) && defined(__x86_64__)
	asm volatile (
		// At entry: rdi = argc, rsi = argv, rdx = envp
		"mov qword ptr [%[argc]], rdi\n" // store argc
		"mov qword ptr [%[argv]], rsi\n" // store argv
		"mov qword ptr [%[envp]], rdx\n" // store envp

		// Align stack to 16 bytes before call
		"and rsp, -16\n"
		"call StartC\n"

		// If returns, exit(rax)
		"mov rdi, rax\n" // exit code
		"mov rax, 0x2000001\n" // macOS sys_exit
		"syscall\n"
		:
		[argc] "=m" (gArgc),
		[argv] "=m" (gArgv),
		[envp] "=m" (gEnvp)
		:
		: "rax","rdi","rsi","rdx","memory"
	);
#elif defined(__APPLE__) && defined(__aarch64__)
	asm volatile (
		// At entry: x0 = argc, x1 = argv, x2 = envp
		"str x0, %[argc]\n" // store argc
		"str x1, %[argv]\n" // store argv
		"str x2, %[envp]\n" // store envp

		// Align stack to 16 bytes before call
		"and sp, sp, #-16\n"
		"bl StartC\n"

		// If returns, exit(x0)
		"mov x16, #1\n" // macOS sys_exit
		"svc #0\n"
		:
		[argc] "=m" (gArgc),
		[argv] "=m" (gArgv),
		[envp] "=m" (gEnvp)
		:
		: "x0","x1","x2","x16","x30","memory"
	);
#elif defined(__linux__) && defined(__x86_64__)
	asm volatile (
		"pop %%rdi\n" // argc
		"mov %%rsp, %%rsi\n" // argv
		"lea 8(%%rsi,%%rdi,8), %%rdx\n" // envp = argv + argc + NULL

		"mov %%rdi, gArgc(%%rip)\n"
		"mov %%rsi, gArgv(%%rip)\n"
		"mov %%rdx, gEnvp(%%rip)\n"

		"sub $8, %%rsp\n" // align stack to 16 before call
		"call StartC\n"

		"mov $"XSTR(SYS_exit)", %%rax\n" // SYS_exit
		"xor %%rdi, %%rdi\n" // exit code 0
		"syscall\n"
		:
		:
		: "rax","rdi","rsi","rdx","memory"
	);
#elif defined(__linux__) && defined(__aarch64__)
	asm volatile (
		// Store argc, argv, envp
		"adrp x0, gArgc@PAGE\n" // x0 = base of gArgc page
		"add  x0, x0, gArgc@PAGEOFF\n"
		"str  w0, [x0]\n" // store argc
		"ldr  x1, [sp, #8]\n" // argv pointer from original x1 on stack
		"str  x1, [x0, #8]\n" // store argv
		"ldr  x2, [sp, #16]\n" // envp pointer from stack
		"str  x2, [x0, #16]\n" // store envp

		// Align stack
		"and sp, sp, #-16\n"

		// Call C entry point
		"bl StartC\n"

		// Exit(0)
		"mov x0, #0\n"
		"mov x8, #93\n"
		"svc #0\n" // SYS_exit
		:
		:
		: "x0","x1","x2","x8","memory"
	);
#else
	#error "Unsupported platform && architecture"
#endif
}