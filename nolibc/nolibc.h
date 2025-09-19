#ifndef NOLIBC_LIBC_H
#define NOLIBC_LIBC_H

#include "types.h"

// ============================
// SYSTEM
// ============================

void exit(s64 status);

// ============================
// STR
// ============================

u64 strlen(const u8* s);
#define strlenK(_s_) ( ( sizeof((_s_)) / sizeof((_s_)[0]) ) - 1 )

// ============================
// PRINT
// ============================

void fPrint(u64 fd, const u8* s);
void fPrint2(u64 fd, const u8* s, u64 len);
#define fPrintK(_fd_, _s_) fPrint2((u64)(_fd_), (u8*)(_s_), strlenK(_s_))
void fPrintln(u64 fd, const u8* s);
void fPrintln2(u64 fd, const u8* s, u64 len);
#define fPrintlnK(_fd_, _s_) fPrintln2((u64)(_fd_), (u8*)(_s_), strlenK(_s_))
void fPrintNewLine(u64 fd);

void print(const u8* s);
void print2(const u8* s, u64 len);
#define printK(_s_) print2((u8*)(_s_), strlenK(_s_))
void println(const u8* s);
void println2(const u8* s, u64 len);
#define printlnK(_s_) println2((u8*)(_s_), strlenK(_s_))
void printNewLine();


void vfPrintF(u64 fd, const u8 *fmt, __builtin_va_list va_list);
void fPrintF(u64 fd, const u8 *fmt, ...);
void printF(const u8 *fmt, ...);

void vfPrintlnF(u64 fd, const u8 *fmt, __builtin_va_list va_list);
void fPrintlnF(u64 fd, const u8 *fmt, ...);
void printlnF(const u8 *fmt, ...);

#endif //NOLIBC_LIBC_H
