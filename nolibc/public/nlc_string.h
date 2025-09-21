#ifndef NOLIBC_NLC_STRING_H
#define NOLIBC_NLC_STRING_H

#include "nlc_types.h"

typedef struct {
	const cStr str;
	const uSize len;
} Str;

#define StrConst(_str_) (const Str) { .str=(_str_), .len=cStrLenK((_str_)) }

u64 cStrLen(const cStr s);
#define cStrLenK(_s_) ( ( sizeof((_s_)) ) - 1 )

#endif //NOLIBC_NLC_STRING_H