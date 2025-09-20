#ifndef NOLIBC_LIBC_H
#define NOLIBC_LIBC_H

#include "nlc_types.h"

// ============================
// FD
// ============================

#define FILE_STDIN 0
#define FILE_STDOUT 1
#define FILE_STDERR 2

// ============================
// FILE FLAGS
// ============================

// Access modes (only one of these)
#define O_RDONLY        0       // Open for reading only
#define O_WRONLY        1       // Open for writing only
#define O_RDWR          2       // Open for reading and writing

// File creation and status flags
#define O_CREAT         0x40    // Create file if it does not exist
#define O_EXCL          0x80    // Error if O_CREAT and the file exists
#define O_NOCTTY        0x100   // Do not assign controlling terminal
#define O_TRUNC         0x200   // Truncate file to zero length
#define O_APPEND        0x400   // Append on each write
#define O_NONBLOCK      0x800   // Non-blocking mode
#define O_DSYNC         0x1000  // Synchronized I/O data integrity
#define FASYNC          0x2000  // Signal-driven I/O
#define O_DIRECT        0x4000  // Minimize cache effects
#define O_LARGEFILE     0x8000  // Allow large files
#define O_DIRECTORY     0x10000 // Must be a directory
#define O_NOFOLLOW      0x20000 // Do not follow symbolic links
#define O_NOATIME       0x40000 // Do not update access time
#define O_CLOEXEC       0x80000 // Close on exec
#define O_SYNC          0x101000 // Synchronous writes (O_DSYNC|O_SYNC)
#define O_PATH          0x200000 // Obtain path without opening file
#define O_TMPFILE       0x410000 // Create unnamed temporary file (Linux >=3.11)

// ============================
// system.c
// ============================

void Exit(s64 status);
s64 FileOpen(const s8* filename, u64 flags);
void FileClose(s64 fd);
s64 FileRead(s64 fd, u8* buf, u64 count);
s64 FileWrite(s64 fd, const u8* buf, u64 count);
s64 FileSize(s64 fd);

// ============================
// memory.c
// ============================

void* MapMem(uSize size);
void UnmapMem(void* ptr, uPtr size);
void Memset(void* ptr, u8 val, uSize size);

typedef struct Arena Arena;
Arena* ArenaNew(u64 size);
void* ArenaAlloc(Arena* arena, uSize size);
void ArenaReset(Arena* arena);
void ArenaFree(Arena* arena);
u64 ArenaRemaining(const Arena* arena);
u64 ArenaSize(const Arena* arena);

// ============================
// string.c
// ============================

u64 StrLen(const s8* s);
#define StrLenK(_s_) ( ( sizeof((_s_)) / sizeof((_s_)[0]) ) - 1 )

// ============================
// print.c
// ============================

// ==== Print =================
// File
void PrintFile(u64 fd, const s8* s);
void PrintFileLen(u64 fd, const s8* s, u64 len);
#define PrintFileK(_fd_, _s_) PrintFileLen((u64)(_fd_), (s8*)(_s_), StrLenK(_s_))
// Out
void Print(const s8* s);
void PrintLen(const s8* s, u64 len);
#define PrintK(_s_) PrintLen((s8*)(_s_), StrLenK(_s_))
// ==== PrintLn ===============
// File
void PrintLnFile(u64 fd, const s8* s);
void PrintLnFileLen(u64 fd, const s8* s, u64 len);
#define PrintLnFileK(_fd_, _s_) PrintLnFileLen((u64)(_fd_), (s8*)(_s_), StrLenK(_s_))
// Out
void PrintLn(const s8* s);
void PrintLnLen(const s8* s, u64 len);
#define PrintLnK(_s_) PrintLnLen((s8*)(_s_), StrLenK(_s_))
// ==== PrintNewLine ===============
void PrintNewLineFile(u64 fd);
void PrintNewLine();
// ==== PrintFmt ===================
void PrintFmtVarFile(u64 fd, const s8 *fmt, __builtin_va_list va_list);
void PrintFmtFile(u64 fd, const s8 *fmt, ...);
void PrintFmt(const s8* fmt, ...);

#endif //NOLIBC_LIBC_H
