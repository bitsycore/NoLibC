#ifndef NOLIBC_LIBC_H
#define NOLIBC_LIBC_H

#include "types.h"

u64 strlen(const u8* s);
u64 puts(const u8* s);
u64 putsLen(const u8* s, u64 len);
u64 putcLr();
#define putsEx(_s_) putsLen(\
	_s_,\
	sizeof(_s_)/sizeof((_s_)[0])\
)
u64 exit(u64 status);

#endif //NOLIBC_LIBC_H
