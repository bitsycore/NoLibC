#ifndef NOLIBC_NLC_MEMORY_H
#define NOLIBC_NLC_MEMORY_H

#include "nlc_types.h"

void* MemoryAlloc(uSize size);
void MemoryFree(void* ptr, uPtr size);
void MemorySet(void* ptr, u8 val, uSize size);

#endif //NOLIBC_NLC_MEMORY_H