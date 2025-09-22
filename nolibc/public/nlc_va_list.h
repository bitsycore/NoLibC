#ifndef NOLIBC_NLC_VALIST_H
#define NOLIBC_NLC_VALIST_H

typedef __builtin_va_list VaList;
#define VaStart(args, n) __builtin_va_start(args, n)
#define VaEnd(args) __builtin_va_end(args)
#define VaCopy(dst, src) __builtin_va_copy(dst, src)
#define VaArg(args, type) __builtin_va_arg(args, type)

#endif //NOLIBC_NLC_VALIST_H