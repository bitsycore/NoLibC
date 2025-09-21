#ifndef NOLIBC_NLC_PRINT_H
#define NOLIBC_NLC_PRINT_H

#include "nlc_string.h"
#include "nlc_types.h"

void Print(const cStr s);
void PrintLen(const cStr s, uSize len);
#define PrintK(_s_) PrintLen((cStr)(_s_), cStrLenK(_s_))

__attribute__((overloadable))
void PrintLn(const cStr s);
__attribute__((overloadable))
void PrintLn(const cStr s, uSize len);
#define PrintLnK(_s_) PrintLn((cStr)(_s_), cStrLenK(_s_))

void PrintNewLine();

void PrintFmt(const cStr fmt, ...);
void PrintFmtV(const cStr fmt, vaList va);

#endif //NOLIBC_NLC_PRINT_H