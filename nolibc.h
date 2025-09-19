#ifndef NOLIBC_LIBC_H
#define NOLIBC_LIBC_H

#ifdef __LP64__
typedef unsigned long		u64;
typedef long				s64;
typedef unsigned long		uPtr;
typedef long				sPtr;
#else
typedef unsigned long long	u64;
typedef long long			s64;
typedef unsigned int		uPtr;
typedef int					sPtr;
#endif

typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;
typedef _Bool boolean;
typedef float f32;
typedef double f64;

#define null ((void*)0)
#define true ((_Bool)(1))
#define false ((bool)(0))

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
