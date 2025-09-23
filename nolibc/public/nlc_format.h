#ifndef NOLIBC_NLC_FORMAT_H
#define NOLIBC_NLC_FORMAT_H
#include "nlc_types.h"

uSize FormatUnsignedToCStr(u64 value, s8 base, cStr out, u32 min_width);
uSize FormatSignedToCStr(s64 val, cStr out);
void FormatFloatToCStr(f64 value, cStr out, u64* outLen, u32 precision);
u64 FormatCStrV(s8* buf, u64 size, const cStr fmt, VaList vaList);
u64 FormatCStr(s8* buf, u64 size, const cStr fmt, ...);


#endif //NOLIBC_NLC_FORMAT_H