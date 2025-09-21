#ifndef NOLIBC_NLC_FILE_H
#define NOLIBC_NLC_FILE_H

#include "nlc_types.h"

int FileOpen(const cStr filename, int flags);
void FileClose(int fd);
s64 FileRead(int fd, u8* buf, u64 count);
s64 FileWrite(int fd, const u8* buf, u64 count);
sSize FileSize(int fd);

// ============================
// FD
// ============================

#define FILE_STDIN 0
#define FILE_STDOUT 1
#define FILE_STDERR 2

// ============================
// FILE FLAGS
// ============================

// Access modes

#define OPEN_READ		0
#define OPEN_WRITE		1
#define OPEN_READWRITE	2

// Flags

#define OPEN_CREATE_IF_NEED        0x40
#define OPEN_EXCL          0x80
#define OPEN_NOCTTY        0x100
#define OPEN_TRUNCATE      0x200
#define OPEN_APPEND        0x400
#define OPEN_NONBLOCK      0x800
#define OPEN_DSYNC         0x1000
#define OPEN_FASYNC        0x2000
#define OPEN_DIRECT        0x4000
#define OPEN_LARGEFILE     0x8000
#define OPEN_DIRECTORY     0x10000
#define OPEN_NOFOLLOW      0x20000
#define OPEN_NOATIME       0x40000
#define OPEN_CLOEXEC       0x80000
#define OPEN_SYNC          0x101000
#define OPEN_PATH          0x200000
#define OPEN_TMPFILE       0x410000

#endif //NOLIBC_NLC_FILE_H