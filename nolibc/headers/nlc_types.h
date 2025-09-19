#ifndef NOLIBC_NLC_TYPES_H
#define NOLIBC_NLC_TYPES_H

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

#endif //NOLIBC_NLC_TYPES_H