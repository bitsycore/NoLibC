#include "nlc.h"
#include "_entry.h"

// ============================
// MARK: Entry point
// ============================

__attribute__((used)) volatile uSize gArgc;
__attribute__((used)) volatile s8** gArgv;
volatile s8** gEnvp;
volatile uPtr* gAuxv;

extern int main(int argc, char** argv, char** envp);

__attribute__((used))
void StartC(long argc, char** argv) {
	argc = gArgc;
	argv = (char**)gArgv;

	s8** envp = &argv[argc + 1];
	gEnvp = (volatile char**)envp;

	while (*envp) {
		envp++;
	}
	gAuxv = (uPtr*)(envp + 1);

	const int status = main((int)argc, argv, (char**)gEnvp);
	SysExit(status);
}

void __attribute__((naked)) _start() {
#if defined(__x86_64__)
	// rsp[0]       : argc
	// rsp[8]       : argv[0]
	// rsp[16]      : argv[1]
	// rsp[8*argc]  : argv[argc] (NULL)
	// rsp[8*argc+8]: envp[0]
	asm volatile (
		"pop %rdi\n" // Pop argc into the first argument register (%rdi)
		"mov %rsp, %rsi\n" // Move argv pointer (current %rsp) into the second argument register (%rsi)
		"mov %rdi, gArgc(%rip)\n" // Save argc
		"mov %rsi, gArgv(%rip)\n" // Save argv
		"call StartC\n" // Call StartC(argc, argv)
	);
#elif defined(__i386__)
	// esp[0]       : argc
	// esp[4]       : argv[0]
	// esp[4*argc+4]: envp[0]
	asm volatile (
		"pop %eax\n" // Pop argc into eax
		"mov %esp, %ebx\n" // Move argv pointer into ebx
		"mov %eax, gArgc\n" // Save argc
		"mov %ebx, gArgv\n" // Save argv
		"push %ebx\n" // push argv
		"push %eax\n" // push argc
		"call StartC\n" // Call StartC(argc, argv)
	);
#elif defined(__aarch64__)
	// For AArch64, argc, argv are passed in registers x0 and x1 by some loaders,
	// but the kernel places them on the stack. Read from the stack for consistency.
	// sp[0]: argc
	// sp[8]: argv[0]
	// ...
	asm volatile (
		"ldr x0, [sp]\n" // Load argc from stack into x0
		"add x1, sp, #8\n" // Calculate the argv address (sp + 8) and put it in x1
		"mov x2, %0\n" // Load address of gArgc into x2
		"str x0, [x2]\n" // Save argc to gArgc
		"mov x2, %1\n" // Load address of gArgv into x2
		"str x1, [x2]\n" // Save argv to gArgv
		"bl StartC\n" // Branch with a link to StartC
		:
		: "r"(&gArgc), "r"(&gArgv)
		: "x0", "x1", "x2", "x30" // x30 is the link register
	);
#elif defined(__arm__)
	// For ARM 32-bit, similar to AArch64, the stack contains the information.
	// sp[0]: argc
	// sp[4]: argv[0]
	// ...
	asm volatile (
		"ldr r0, [sp]\n" // Load argc from stack into r0
		"add r1, sp, #4\n" // Calculate argv address (sp + 4) into r1
		"ldr r2, =gArgc\n" // Load address of gArgc into r2
		"str r0, [r2]\n" // Save argc
		"ldr r2, =gArgv\n" // Load address of gArgv into r2
		"str r1, [r2]\n" // Save argv
		"bl StartC\n" // Branch with link to StartC
	);
#endif
}