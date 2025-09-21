#include "public/nlc_memory.h"

#include "private/entry.h"
#include "private/intrinsic.h"
#include "private/system.h"
#include "public/nlc_types.h"

#define AT_NULL     0
#define AT_PAGESZ   6

static uSize GetPageSize() {
	uSize pageSize = 4096;
#if __linux__
	static uSize PAGE_SIZE_CALCULATED = 0;
	if (PAGE_SIZE_CALCULATED != 0) return PAGE_SIZE_CALCULATED;
	const uPtr* stackPtr = (uPtr*)gAuxv;
	while (stackPtr[0] != AT_NULL) {
		if (stackPtr[0] == AT_PAGESZ) {
			pageSize = stackPtr[1];
			break;
		}
		stackPtr += 2;
	}
	PAGE_SIZE_CALCULATED = pageSize;
#endif
	return pageSize;
}

void* MemoryAlloc(const uSize size) {
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

void MemoryFree(void *ptr, const uPtr size) {
	const uSize pageSize = GetPageSize();
	const uSize aligned = size + pageSize - 1 & ~(pageSize - 1);
	SysCall(SYS_munmap, (uPtr)ptr, aligned, 0, 0, 0, 0);
}

void MemorySet(void *ptr, const u8 val, const uSize size) {
	memset(ptr, val, size);
}