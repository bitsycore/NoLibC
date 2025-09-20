#include "public/nlc.h"

#if defined(__clang__) && !defined(__APPLE__)

__attribute__((used))
void* memset(void* ptr, const int value, uSize num)  {
    unsigned char* p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

__attribute__((used))
void* memmove(void *dst, const void *src, uSize n) {
    if (n == 0 || dst == src) return dst;

    u8 *d = dst;
    const u8 *s = src;

    if (d < s) {
        const uPtr align_mask = sizeof(uPtr) - 1;
        while (n && ((uPtr)d & align_mask) != 0 && n) {
            *d++ = *s++;
            --n;
        }
        uPtr *dw = (uPtr *)d;
        const uPtr *sw = (const uPtr *)s;
        while (n >= sizeof(uPtr)) {
            *dw++ = *sw++;
            n -= sizeof(uPtr);
        }
        d = (u8 *)dw;
        s = (const u8 *)sw;
        while (n--) *d++ = *s++;
    } else {
        // copy backward
        d += n;
        s += n;
        const uPtr align_mask = sizeof(uPtr) - 1;
        while (n && ((uPtr)d & align_mask) != 0) {
            *--d = *--s;
            --n;
        }
        uPtr *dw = (uPtr *)d;
        const uPtr *sw = (const uPtr *)s;
        while (n >= sizeof(uPtr)) {
            *--dw = *--sw;
            n -= sizeof(uPtr);
        }
        d = (u8 *)dw;
        s = (const u8 *)sw;
        while (n--) *--d = *--s;
    }

    return dst;
}

#elif defined(__APPLE__)

__attribute__((used))
void bzero(void *s, uPtr n) {
    unsigned char *p = s;
    while (n--) {
        *p++ = 0;
    }
}

#endif