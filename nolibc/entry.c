#include "private/entry.h"

#include "private/system.h"
#include "public/nlc_system.h"

// ============================
// MARK: Entry point
// ============================

NLC_ATTR_USED volatile uSize gArgc;
NLC_ATTR_USED volatile cStr* gArgv;
volatile cStr* gEnvp;
volatile uPtr* gAuxv;

extern int main(int argc, char** argv);

#if defined(__linux__)
NLC_ATTR_USED
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
NLC_ATTR_USED
void StartC(long argc, char** argv) {
	argc = gArgc;
	argv = (char**)gArgv;

	// TODO: ENVP

	const int status = main((int)argc, argv);
	SysExit(status);
}
#endif

NLC_ATTR_NAKED
void _start() { // NOLINT(*-reserved-identifier)
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
		// At entry: rsp -> argc
		"pop %%rdi\n"           // rdi = argc
		"mov %%rsp, %%rsi\n"    // rsi = argv (rsp points to argv[0])
		"mov %%rsi, %%rdx\n"    // rdx = envp pointer start
		"mov %%rdi, gArgc(%%rip)\n"
		"mov %%rsi, gArgv(%%rip)\n"
		"lea (%%rsi,%%rdi,8), %%rdx\n" // envp = argv + argc
		"mov %%rdx, gEnvp(%%rip)\n"

		// Align stack to 16 bytes before call
		"andq $-16, %%rsp\n"
		"call StartC\n"

		// Should never return; if it does, exit
		"mov $60, %%rax\n"  // SYS_exit
		"xor %%rdi, %%rdi\n" // exit code 0
		"syscall\n"
		:
		:
		: "rax", "rdi", "rsi", "rdx", "memory"
	);
#elif defined(__i386__)
	asm volatile (
		// Stack layout on entry:
		// esp -> argc
		//       argv[0], argv[1], ..., argv[argc-1], NULL
		//       envp[0], ...
		"pop %%eax\n"         // eax = argc
		"mov %%esp, %%ebx\n"  // ebx = argv
		"mov %%eax, gArgc\n"
		"mov %%ebx, gArgv\n"

		// Compute envp: argv + argc + 1
		"mov %%eax, %%ecx\n"  // ecx = argc
		"add $1, %%ecx\n"
		"shl $2, %%ecx\n"     // ecx = (argc + 1) * 4 bytes
		"add %%ebx, %%ecx\n"  // ecx = envp pointer
		"mov %%ecx, gEnvp\n"

		// Push arguments for StartC (cdecl)
		"push %%ecx\n"        // envp
		"push %%ebx\n"        // argv
		"push %%eax\n"        // argc
		"call StartC\n"

		// Should not return; exit if it does
		"mov $1, %%eax\n"     // SYS_exit
		"xor %%ebx, %%ebx\n"
		"int $0x80\n"
		:
		:
		: "eax", "ebx", "ecx", "memory"
	);
#elif  defined(__aarch64__)
	asm volatile(
		// Entry: sp -> argc
		"ldr x0, [sp]\n"          // argc
		"add x1, sp, #8\n"        // argv
		// Save globals
		"adr x2, gArgc\n"
		"str x0, [x2]\n"
		"adr x2, gArgv\n"
		"str x1, [x2]\n"
		"adr x2, gEnvp\n"
		"add x3, x1, x0, lsl #3\n" // argv + argc*8
		"add x3, x3, #8\n"          // skip NULL -> envp
		"str x3, [x2]\n"
		// Align stack to 16 bytes before call
		"and sp, sp, #-16\n"
		// Call C entry
		"bl StartC\n"
		// Exit if it returns
		"mov x8, #93\n"
		"mov x0, #0\n"
		"svc #0\n"
		:
		:
		: "x0","x1","x2","x3","x30","memory"
	);

#elif defined(__arm__)
	register uint32_t *r2 asm("r2") = &gArgc;
	register uint32_t *r3 asm("r3") = &gArgv;
	register uint32_t *r4 asm("r4") = &gEnvp;
	asm volatile(
		"ldr r0, [sp]\n"           // argc
		"add r1, sp, #4\n"         // argv
		// Save globals
		"str r0, [r2]\n"           // gArgc
		"str r1, [r3]\n"           // gArgv
		"add r5, r1, r0, lsl #2\n" // argv + argc*4
		"add r5, r5, #4\n"          // skip NULL -> envp
		"str r5, [r4]\n"           // gEnvp
		// Call C entry
		"mov r0, r0\n"             // argc
		"mov r1, r1\n"             // argv
		"mov r2, r5\n"             // envp
		"bl StartC\n"
		// Exit if it returns
		"mov r7, #1\n"             // SYS_exit
		"mov r0, #0\n"             // exit code
		"svc #0\n"
		:
		:
		: "r0","r1","r2","r3","r4","r5","lr","memory"
	);
#else
#error "Unsupported architecture"
#endif
#endif
}
