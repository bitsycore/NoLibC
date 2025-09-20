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

// Access modes
#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2

// Flags
#define O_CREAT         0x40
#define O_EXCL          0x80
#define O_NOCTTY        0x100
#define O_TRUNC         0x200
#define O_APPEND        0x400
#define O_NONBLOCK      0x800
#define O_DSYNC         0x1000
#define FASYNC          0x2000
#define O_DIRECT        0x4000
#define O_LARGEFILE     0x8000
#define O_DIRECTORY     0x10000
#define O_NOFOLLOW      0x20000
#define O_NOATIME       0x40000
#define O_CLOEXEC       0x80000
#define O_SYNC          0x101000
#define O_PATH          0x200000
#define O_TMPFILE       0x410000

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

#define StrConst(_str_) (Str) { .str=_str_, .len=StrLenK(_str_) }

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
