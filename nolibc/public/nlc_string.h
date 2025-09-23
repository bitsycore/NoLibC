#ifndef NOLIBC_NLC_STRING_H
#define NOLIBC_NLC_STRING_H

#include "nlc_types.h"
#include "nlc_varg.h"

typedef struct {
	const cStr str;
	const uSize len;
} Str;

#define StrConst(_str_) (const Str) { .str=(_str_), .len=cStrLenK((_str_)) }
#define StrParamLen(_str_) (_str_), cStrLenK((_str_))
u64 cStrLen(const cStr s);
#define cStrLenK(_s_) ( ( sizeof((_s_)) ) - 1 )
u64 FormatCStr(s8* buf, u64 size, const cStr fmt, ...);
u64 FormatCStrV(s8* buf, u64 size, const cStr fmt, VaList vaList);

#endif //NOLIBC_NLC_STRING_H