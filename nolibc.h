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

void exit(s64 status);

// ============================
// STR
// ============================

u64 strlen(const s8* s);
#define strlenK(_s_) ( ( sizeof((_s_)) / sizeof((_s_)[0]) ) - 1 )

// ============================
// PRINT
// ============================

// ==== Print =================
// File
void printFile(u64 fd, const s8* s);
void printFileLen(u64 fd, const s8* s, u64 len);
#define printFileK(_fd_, _s_) printFileLen((u64)(_fd_), (s8*)(_s_), strlenK(_s_))
// Out
void print(const s8* s);
void printLen(const s8* s, u64 len);
#define printK(_s_) printLen((s8*)(_s_), strlenK(_s_))
// ==== PrintLn ===============
// File
void printLnFile(u64 fd, const s8* s);
void printLnFileLen(u64 fd, const s8* s, u64 len);
#define printLnFileK(_fd_, _s_) printLnFileLen((u64)(_fd_), (s8*)(_s_), strlenK(_s_))
// Out
void printLn(const s8* s);
void printLnLen(const s8* s, u64 len);
#define printLnK(_s_) printLnLen((s8*)(_s_), strlenK(_s_))
// ==== PrintNewLine ===============
void printNewLineFile(u64 fd);
void printNewLine();
// ==== PrintFmt ===================
void printFmtVarFile(u64 fd, const s8 *fmt, __builtin_va_list va_list);
void printFmtFile(u64 fd, const s8 *fmt, ...);
void printFmt(const s8* fmt, ...);
// ==== PrintLnFmt =================
void printLnFmtVarFile(u64 fd, const s8 *fmt, __builtin_va_list va_list);
void printLnFmtFile(u64 fd, const s8 *fmt, ...);
void printLnFmt(const s8 *fmt, ...);

#endif //NOLIBC_LIBC_H
