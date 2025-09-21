#include "public/nlc.h"

NLC_ATTR_USED
void* memset(void* ptr, const int value, uSize num)  {
    u8* p = ptr;

    // Fill the first bytes until p is aligned to uSize
    const uSize align = sizeof(uSize);
    while (num && ((uPtr)p % align)) {
        *p++ = (unsigned char)value;
        --num;
    }

    // Prepare chunk
    uSize val = (u8)value;
    val |= val << 8;
    val |= val << 16;
#if __LP64__
    val |= val << 32; // 64-bit
#endif

    // Fill memory in chunks
    uSize* p64 = (uSize*)p;
    while (num >= sizeof(uSize)) {
        *p64++ = val;
        num -= sizeof(uSize);
    }

    // Fill remaining bytes
    p = (u8*)p64;
    while (num--) {
        *p++ = (u8)value;
    }

    return ptr;
}

#if defined(__clang__) && !defined(__APPLE__)

NLC_ATTR_USED
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

NLC_ATTR_USED
void* memcpy(void* dest, const void* src, uSize n) {
	return memmove(dest, src, n);
}

#elif defined(__APPLE__)

NLC_ATTR_USED
void bzero(void *s, uSize n) {
    memset(s, 0, n);
}

#endif