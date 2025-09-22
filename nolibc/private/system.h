#ifndef NOLIBC_SYSCALL_H
#define NOLIBC_SYSCALL_H

#include "../public/nlc_system.h"
#include "../public/nlc_types.h"

// ============================
// FLAGS
// ============================*

#define SEEK_SET		0
#define SEEK_CUR		1
#define SEEK_END		2

#define PROT_NONE		0x0
#define PROT_READ		0x1
#define PROT_WRITE		0x2
#define PROT_EXEC		0x4

#define MAP_SHARED      0x01
#define MAP_PRIVATE     0x02
#define MAP_FIXED       0x10

#if defined(__APPLE__)

	#define MAP_ANON        0x1000
	#define MAP_ANONYMOUS   MAP_ANON

#elif defined(__linux__)

	#define MAP_ANONYMOUS   0x20
	#define MAP_ANON        MAP_ANONYMOUS

#endif

// ============================
// SYSCALL NUMBERS
// ============================*

#if defined(__linux__)

	# if defined(__x86_64__)

		# define SYS_read      0
		# define SYS_write     1
		# define SYS_open      2
		# define SYS_close     3
		# define SYS_stat      4
		# define SYS_fstat     5
		# define SYS_lseek     8
		# define SYS_mmap      9
		# define SYS_ioctl     16
		# define SYS_pread64   17
		# define SYS_pwrite64  18
		# define SYS_munmap    11
		# define SYS_exit      60

	# elif defined(__i386__)

		# define SYS_read      3
		# define SYS_write     4
		# define SYS_open      5
		# define SYS_close     6
		# define SYS_stat      106
		# define SYS_fstat     108
		# define SYS_lseek     19
		# define SYS_mmap      90
		# define SYS_munmap    91
		# define SYS_pread     180
		# define SYS_pread64   333
		# define SYS_pwrite    181
		# define SYS_pwrite64  334
		# define SYS_exit      1
		# define SYS_fcntl     92
		# define SYS_getdents  141
		# define SYS_mprotect  125
		# define SYS_brk       45

	# elif defined(__aarch64__)

		# define SYS_read      63
		# define SYS_write     64
		# define SYS_open      56
		# define SYS_close     57
		# define SYS_fstat     80
		# define SYS_lseek     62
		# define SYS_mmap      222
		# define SYS_munmap    215
		# define SYS_exit      93

	# elif defined(__arm__)

		# define SYS_read      3
		# define SYS_write     4
		# define SYS_open      5
		# define SYS_close     6
		# define SYS_lseek     19
		# define SYS_mmap      192
		# define SYS_munmap    91
		# define SYS_exit      1

	# else

		# error "unsupported linux arch"

	# endif

#elif defined(__APPLE__)

	# if defined(__x86_64__) || defined(__aarch64__)

		# define SYS_read		3
		# define SYS_write		4
		# define SYS_open		5
		# define SYS_close		6
		# define SYS_exit		1
		# define SYS_ioctl		54
		# define SYS_fstat		189
		# define SYS_stat		188
		# define SYS_lseek		199
		# define SYS_pread		173
		# define SYS_pwrite		174
		# define SYS_munmap		73
		# define SYS_mmap		197

	# else

		# error "unsupported macos arch"

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

sPtr SysOpen(const char* pathname, u64 flags, u64 mode);
sPtr SysClose(u64 fd);
sPtr SysRead(u64 fd, u8* buf, u64 count);
sPtr SysWrite(u64 fd, const u8* buf, u64 count);
NLC_ATTR_NO_RETURN
void SysExit(s64 status);
sPtr SysLSeek(u64 fd, u64 offset, u64 whence);
sPtr SysFStat(u64 fd, u8* buf);

#endif //NOLIBC_SYSCALL_H