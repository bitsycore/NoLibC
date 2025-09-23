#include "public/nlc_string.h"

#include "public/nlc_stringbuffer.h"
#include "public/nlc_varg.h"

#ifdef __LP64__
#define PTR_SIZE 8
#define MASK1 0x0101010101010101ULL
#define MASK2 0x8080808080808080ULL
#else
#define PTR_SIZE 4
#define MASK1 0x01010101U
#define MASK2 0x80808080U
#endif

uSize cStrLen(const cStr s) {
	const u8 *ptr = (const u8*)s;

	// Align to word size
	while (((uPtr)ptr & (PTR_SIZE-1)) != 0) {
		if (*ptr == 0) return ptr - (const u8*)s;
		ptr++;
	}

	const uPtr* ptrWord = (const uPtr*)ptr;
	while (1) {
		const uPtr val = *ptrWord;
		if ((val - MASK1) & ~val & MASK2) {
			const u8* bytes = (const u8*)ptrWord;
			for (int i = 0; i < PTR_SIZE; i++)
				if (bytes[i] == 0) return bytes + i - (const u8*)s;
		}
		ptrWord++;
	}
}

u64 cStrCmp(const cStr s1, const cStr s2) {
	const u8 *p1 = (const u8*)s1;
	const u8 *p2 = (const u8*)s2;

	// Align pointers
	while (((uPtr)p1 & (PTR_SIZE-1)) != 0 && *p1) {
		if (*p1 != *p2) return (u8)*p1 - (u8)*p2;
		p1++; p2++;
	}

	const uPtr* p1_64 = (const uPtr*)p1;
	const uPtr* p2_64 = (const uPtr*)p2;

	while (1) {
		const uPtr v1 = *p1_64;
		const uPtr v2 = *p2_64;
		const uPtr xor = v1 ^ v2;

		// If any byte differs or zero is present
		if (xor != 0) {
			const u8 *b1 = (const u8*)p1_64;
			const u8 *b2 = (const u8*)p2_64;
			for (int i = 0; i < PTR_SIZE; i++) {
				if (b1[i] != b2[i])
					return (u8)b1[i] - (u8)b2[i];
				if (b1[i] == 0)
					return 0;
			}
		}

		p1_64++;
		p2_64++;
	}
}

u64 cStrCat(cStr dst, const cStr src) {
	while (*dst) dst++;
	while (*src) *dst++ = *src++;
	*dst = '\0';
	return 0;
}

u64 cStrCopy(cStr dst, const cStr src) {
	while (*src) *dst++ = *src++;
	*dst = '\0';
	return 0;
}