#ifndef NOLIBC_NLC_MEMORY_H
#define NOLIBC_NLC_MEMORY_H

#include "nlc_types.h"

void* MemoryPageAlloc(uSize size);
void MemoryPageFree(void* ptr, uPtr size);
void MemorySet(void* ptr, u8 val, uSize size);

#endif //NOLIBC_NLC_MEMORY_H