#include "public/nlc_types.h"

#ifdef __LP64__

u64 StrLen(const s8 *s) {
	const u8 *ptr = (const u8*)s;

	// Align to 8 bytes
	while (((uPtr)ptr & 7) != 0) {
		if (*ptr == 0) return ptr - (const u8*)s;
		ptr++;
	}

	const u64* ptr64 = (const u64*)ptr;
	while (1) {
		const u64 val = *ptr64;
		if ((val - 0x0101010101010101ULL) & ~val & 0x8080808080808080ULL) {
			const u8* p8 = (const u8*)ptr64;
			for (int i = 0; i < 8; i++)
				if (p8[i] == 0) return p8 + i - (const u8*)s;
		}
		ptr64++;
	}
}

u64 StrCmp(const s8 *s1, const s8 *s2) {
	const u8 *p1 = (const u8*)s1;
	const u8 *p2 = (const u8*)s2;

	// Align pointers
	while (((uPtr)p1 & 7) != 0 && *p1) {
		if (*p1 != *p2) return (u8)*p1 - (u8)*p2;
		p1++; p2++;
	}

	const u64* p1_64 = (const u64*)p1;
	const u64* p2_64 = (const u64*)p2;

	while (1) {
		const u64 v1 = *p1_64;
		const u64 v2 = *p2_64;
		const u64 xor = v1 ^ v2;

		// If any byte differs or zero is present
		if (xor != 0) {
			const u8 *b1 = (const u8*)p1_64;
			const u8 *b2 = (const u8*)p2_64;
			for (int i = 0; i < 8; i++) {
				if (b1[i] != b2[i])
					return (u8)b1[i] - (u8)b2[i];
				if (b1[i] == 0)
					return 0;  // both are zero
			}
		}

		p1_64++; p2_64++;
	}
}

#else

u64 StrLen(const s8 *s) {
	const u8 *ptr = (const u8*)s;

	// Align to 4 bytes
	while (((uPtr)ptr & 3) != 0) {
		if (*ptr == 0) return ptr - (const u8*)s;
		ptr++;
	}

	const u32* ptr32 = (const u32*)ptr;
	while (1) {
		const u32 val = *ptr32;
		if ((val - 0x01010101U) & ~val & 0x80808080U) {
			const u8* p8 = (const u8*)ptr32;
			for (int i = 0; i < 4; i++)
				if (p8[i] == 0) return p8 + i - (const u8*)s;
		}
		ptr32++;
	}
}

u64 StrCmp(const s8 *s1, const s8 *s2) {
	const u32 *p1_32;
	const u32 *p2_32;
	const u8 *p1 = (const u8*)s1;
	const u8 *p2 = (const u8*)s2;

	// Align pointers
	while (((uintptr_t)p1 & 3) != 0 && *p1) {
		if (*p1 != *p2) return (u8)*p1 - (u8)*p2;
		p1++; p2++;
	}

	p1_32 = (const u32*)p1;
	p2_32 = (const u32*)p2;

	while (1) {
		u32 v1 = *p1_32;
		u32 v2 = *p2_32;
		u32 xor = v1 ^ v2;

		// If any byte differs or zero is present
		if (xor != 0) {
			const u8 *b1 = (const u8*)p1_32;
			const u8 *b2 = (const u8*)p2_32;
			for (int i = 0; i < 4; i++) {
				if (b1[i] != b2[i])
					return (u8)b1[i] - (u8)b2[i];
				if (b1[i] == 0)
					return 0;
			}
		}

		p1_32++; p2_32++;
	}
}

#endif

u64 StrCat(s8* dst, const s8* src) {
	while (*dst) dst++;
	while (*src) *dst++ = *src++;
	*dst = '\0';
	return 0;
}

u64 StrCopy(s8* dst, const s8* src) {
	while (*src) *dst++ = *src++;
	*dst = '\0';
	return 0;
}