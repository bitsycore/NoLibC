

#include "nlc_types.h"
#include "_syscall.h"
#include "_system.h"

#define AT_NULL     0
#define AT_PAGESZ   6

uSize GetPageSize() {
	uSize pageSize = 4096;
#if __linux__
	static uSize PAGE_SIZE_CALCULATED = 0;
	if (PAGE_SIZE_CALCULATED != 0) return PAGE_SIZE_CALCULATED;
	// auxv
	const uPtr* stackPtr = (uPtr*)gAuxv;
	while (stackPtr[0] != AT_NULL) {
		if (stackPtr[0] == AT_PAGESZ) {
			pageSize = stackPtr[1];
			break;
		}
		stackPtr += 2;
	}
	PAGE_SIZE_CALCULATED = pageSize;
	return pageSize;
#else
	return pageSize;
#endif
}

void* Malloc(const uSize size) {
	const uSize pageSize = GetPageSize();
	const uSize aligned = (size + pageSize - 1) & ~(pageSize - 1);

	void* p = (void*)SysCall(
		SYS_mmap,
		0,
		aligned,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,
		-1,
		0
	);

	return p == (void*)-1 ? null : p;
}

void Free(void *ptr, const uPtr size) {
	const uSize pageSize = GetPageSize();
	const uSize aligned = size + pageSize - 1 & ~(pageSize - 1);
	SysCall(SYS_munmap, (uPtr)ptr, aligned, 0, 0, 0, 0);
}

void Memset(void *ptr, const u8 val, const uSize size) {
	u8* p = (u8*)ptr;
	for (uSize i = 0; i < size; i++) {
		p[i] = val;
	}
}