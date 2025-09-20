#ifndef NOLIBC_SYSCALL_H
#define NOLIBC_SYSCALL_H

#include "../public/nlc_types.h"

// ============================
// FLAGS
// ============================*

/* Protection flags */
#define PROT_NONE       0x0
#define PROT_READ       0x1
#define PROT_WRITE      0x2
#define PROT_EXEC       0x4

/* Mapping flags */
#define MAP_SHARED      0x01
#define MAP_PRIVATE     0x02
#define MAP_FIXED       0x10
#define MAP_ANONYMOUS   0x20

// ============================
// SYSCALL NUMBERS
// ============================*

#if defined(__linux__)

# if defined(__x86_64__)
#  define SYS_read     0
#  define SYS_write    1
#  define SYS_open     2
#  define SYS_close    3
#  define SYS_mmap     9
#  define SYS_munmap   11
#  define SYS_exit     60

# elif defined(__i386__)
#  define SYS_read     3
#  define SYS_write    4
#  define SYS_open     5
#  define SYS_close    6
#  define SYS_mmap     90
#  define SYS_munmap   91
#  define SYS_exit     1

# elif defined(__aarch64__)
#  define SYS_read     63
#  define SYS_write    64
#  define SYS_open     56
#  define SYS_close    57
#  define SYS_mmap     222
#  define SYS_munmap   215
#  define SYS_exit     93

# elif defined(__arm__)
#  define SYS_read     3
#  define SYS_write    4
#  define SYS_open     5
#  define SYS_close    6
#  define SYS_mmap     192
#  define SYS_munmap   91
#  define SYS_exit     1

# else
#  error "unsupported linux arch"
# endif

#elif defined(__APPLE__)

# if defined(__x86_64__) || defined(__aarch64__)
#  define SYS_read     3
#  define SYS_write    4
#  define SYS_open     5
#  define SYS_close    6
/* macOS uses Mach syscalls; mmap/munmap are not direct syscalls */
#  define SYS_exit     1
# else
#  error "unsupported macos arch"
# endif

#else
# error "unsupported platform"
#endif

sPtr SysCall(
	sPtr n,
	uPtr a,
	uPtr b,
	uPtr c,
	uPtr d,
	uPtr e,
	uPtr f
);

void SysExit(s64 status);
sPtr SysWrite(u64 fd, const u8* buf, u64 count);


#endif //NOLIBC_SYSCALL_H