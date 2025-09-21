#ifndef NOLIBC_NLC_SYSTEM_H
#define NOLIBC_NLC_SYSTEM_H

#define NLC_ATTR_USED			__attribute__ ((used))

#define NLC_ATTR_NO_RETURN		__attribute__ ((noreturn))
#define NLC_ATTR_NO_INLINE		__attribute__ ((noinline))
#define NLC_ATTR_ALWAYS_INLINE	__attribute__ ((always_inline))
#define NLC_ATTR_OVERLOADABLE	__attribute__ ((overloadable))
#define NLC_ATTR_NAKED			__attribute__ ((naked))

#define NLC_ATTR_PURE			__attribute__ ((pure))
#define NLC_ATTR_CONST			__attribute__ ((const))

#define NLC_ATTR_ALIGN(x)		__attribute__ ((aligned(x)))
#define NLC_ATTR_PACKED			__attribute__ ((packed))

#define NLC_ATTR_MALLOC			__attribute__ ((malloc))
#define NLC_ATTR_PRINTF(x,y)	__attribute__ ((format(printf, x, y)))

#define NLC_ATTR_WEAK			__attribute__ ((weak))
#define NLC_ATTR_SECTION(x)		__attribute__ ((section(x)))
#define NLC_ATTR_ALIAS(x)		__attribute__ ((alias(x)))

#define NLC_ATTR_DEPRECATED			__attribute__ ((deprecated))
#define NLC_ATTR_DEPRECATED_MSG(x)	__attribute__ ((deprecated(x)))

#define NLC_UNREACHABLE() __builtin_unreachable()

void Exit(int status);

#endif //NOLIBC_NLC_SYSTEM_H