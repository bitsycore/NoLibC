#ifndef NOLIBC_SYSCALL_H
#define NOLIBC_SYSCALL_H

#include "types.h"

#if defined(__x86_64__)
# define SYS_write 1
# define SYS_exit  60
#elif defined(__aarch64__)
# define SYS_write 64
# define SYS_exit  93
#else
# error "unsupported arch"
#endif

u64 syscall(u64 n, u64 a, u64 b, u64 c, u64 d, u64 e, u64 f);

#endif //NOLIBC_SYSCALL_H