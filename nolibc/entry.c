#include "private/entry.h"

#include "private/system.h"
#include "public/nlc_string.h"

// ============================
// MARK: Entry point
// ============================

__attribute__((used)) volatile uSize gArgc;
__attribute__((used)) volatile cStr* gArgv;
volatile cStr* gEnvp;
volatile uPtr* gAuxv;

extern int main(int argc, char** argv);

#if defined(__linux__)
__attribute__((used))
void StartC(long argc, char** argv) {
	argc = (long)gArgc;
	argv = (char**)gArgv;

	cStr* envp = &argv[argc + 1];
	gEnvp = (volatile char**)envp;

	while (*envp) {
		envp++;
	}
	gAuxv = (uPtr*)(envp + 1);

	const int status = main((int)argc, argv);
	SysExit(status);
}
#elif defined(__APPLE__)
__attribute__((used))
void StartC(long argc, char** argv) {
	argc = gArgc;
	argv = (char**)gArgv;

	// TODO: ENVP

	const int status = main((int)argc, argv);
	SysExit(status);
}
#endif

void __attribute__((naked)) _start() {
#if defined(__APPLE__)
#if defined(__x86_64__)
	asm volatile (
		"pop %rdi\n" /* argc */
		"mov %rsp, %rsi\n" /* argv */
		"mov %rdi, gArgc(%rip)\n"
		"mov %rsi, gArgv(%rip)\n"
		"call StartC\n"
		"mov %eax, %edi\n" /* return code */
		"mov $0x2000001, %rax\n" /* sys_exit */
		"syscall\n"
	);
#elif defined(__i386__)
	asm volatile (
		"pop %eax\n" /* argc */
		"mov %esp, %ebx\n" /* argv */
		"mov %eax, gArgc\n"
		"mov %ebx, gArgv\n"
		"push %eax\n"
		"push %ebx\n"
		"call StartC\n"
		"mov %eax, %ebx\n" /* return code */
		"mov $1, %eax\n" /* sys_exit */
		"int $0x80\n"
	);
#elif defined(__aarch64__)
	asm volatile (
		"ldr x0, [sp]\n" /* argc */
		"add x1, sp, #8\n" /* argv */
		"str x0, %[argc]\n"
		"str x1, %[argv]\n"
		"bl StartC\n"
		"mov x0, x0\n" /* return code */
		"mov x16, #1\n" /* sys_exit */
		"svc #0\n"
		:
		[argc] "=m" (gArgc),
		[argv] "=m" (gArgv)
		:
		: "x0","x1","x16","x30"
	);
#elif defined(__arm__)
	asm volatile (
		"ldr r0, [sp]\n" /* argc */
		"add r1, sp, #4\n" /* argv */
		"ldr r2, =gArgc\n"
		"str r0, [r2]\n"
		"ldr r2, =gArgv\n"
		"str r1, [r2]\n"
		"bl StartC\n"
		"mov r0, r0\n" /* return code */
		"mov r7, #1\n" /* sys_exit */
		"svc 0\n"
	);
#else
#error "Unsupported architecture"
#endif
#elif defined(__linux__)
#if defined(__x86_64__)
	asm volatile (
		"pop %rdi\n" // Pop argc into the first argument register (%rdi)
		"mov %rsp, %rsi\n" // Move argv pointer (current %rsp) into the second argument register (%rsi)
		"mov %rdi, gArgc(%rip)\n" // Save argc
		"mov %rsi, gArgv(%rip)\n" // Save argv
		"call StartC\n" // Call StartC(argc, argv)
	);
#elif defined(__i386__)
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
	asm volatile (
		"ldr r0, [sp]\n" // Load argc from stack into r0
		"add r1, sp, #4\n" // Calculate argv address (sp + 4) into r1
		"ldr r2, =gArgc\n" // Load address of gArgc into r2
		"str r0, [r2]\n" // Save argc
		"ldr r2, =gArgv\n" // Load address of gArgv into r2
		"str r1, [r2]\n" // Save argv
		"bl StartC\n" // Branch with link to StartC
	);
#else
#error "Unsupported architecture"
#endif
#endif
}
