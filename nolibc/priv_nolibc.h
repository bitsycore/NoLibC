#ifndef NOLIBC_SYSCALL_H
#define NOLIBC_SYSCALL_H

#include "../nolibc.h"

// ============================
// SYSCALL NUMBERS
// ============================

#if defined(__x86_64__)
# define SYS_read   0
# define SYS_write  1
# define SYS_open   2
# define SYS_close  3
# define SYS_exit   60
#elif defined(__i386__)
# define SYS_read   3
# define SYS_write  4
# define SYS_open   5
# define SYS_close  6
# define SYS_exit   1
#elif defined(__aarch64__)
# define SYS_read   63
# define SYS_write  64
# define SYS_open   56
# define SYS_close  57
# define SYS_exit   93
#elif defined(__arm__)
# define SYS_read   3
# define SYS_write  4
# define SYS_open   5
# define SYS_close  6
# define SYS_exit   1
#else
# error "unsupported arch"
#endif

sPtr syscall(
	sPtr n,
	uPtr a,
	uPtr b,
	uPtr c,
	uPtr d,
	uPtr e,
	uPtr f
);

sPtr write(u64 fd, const u8* buf, u64 count);

#endif //NOLIBC_SYSCALL_H