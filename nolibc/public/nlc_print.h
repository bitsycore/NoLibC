#ifndef NOLIBC_NLC_PRINT_H
#define NOLIBC_NLC_PRINT_H

#include "nlc_string.h"
#include "nlc_types.h"

// ==== Print =================

void PrintFile(int fd, const cStr s);
void PrintFileLen(int fd, const cStr s, uSize len);
#define PrintFileK(_fd_, _s_) PrintFileLen((int)(_fd_), (cStr)(_s_), cStrLenK(_s_))

void Print(const cStr s);
void PrintLen(const cStr s, uSize len);
#define PrintK(_s_) PrintLen((cStr)(_s_), cStrLenK(_s_))

// ==== PrintLn ===============

void PrintLnFile(int fd, const cStr s);
void PrintLnFileLen(int fd, const cStr s, uSize len);
#define PrintLnFileK(_fd_, _s_) PrintLnFileLen((int)(_fd_), (cStr)(_s_), cStrLenK(_s_))

void PrintLn(const cStr s);
void PrintLnLen(const cStr s, uSize len);
#define PrintLnK(_s_) PrintLnLen((cStr)(_s_), cStrLenK(_s_))

// ==== PrintNewLine ===============

void PrintNewLineFile(int fd);
void PrintNewLine();

// ==== PrintFmt ===================

void PrintFmtVarFile(int fd, const cStr fmt, __builtin_va_list va_list);
void PrintFmtFile(int fd, const cStr fmt, ...);
void PrintFmt(const cStr fmt, ...);

#endif //NOLIBC_NLC_PRINT_H