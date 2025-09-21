#ifndef NOLIBC_NLC_ARENA_H
#define NOLIBC_NLC_ARENA_H

#include "nlc_types.h"

typedef struct Arena Arena;
Arena* ArenaNew(uSize size);
void* ArenaAlloc(Arena* arena, uSize size);
void ArenaReset(Arena* arena);
void ArenaFree(Arena* arena);
uSize ArenaRemaining(const Arena* arena);
uSize ArenaSize(const Arena* arena);

#endif //NOLIBC_NLC_ARENA_H