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
// SYSTEM
// ============================

void SysExit(s64 status);

// ============================
// STR
// ============================

u64 StrLen(const s8* s);
#define StrLenK(_s_) ( ( sizeof((_s_)) / sizeof((_s_)[0]) ) - 1 )

// ============================
// PRINT
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
