#include "public/nlc.h"
#include "public/nlc_types.h"

typedef struct Arena {
	uSize size;
	uSize used;
	u8 const data[];
} Arena;

Arena* ArenaNew(const uSize size) {
	const uSize totalSize = sizeof(Arena) + size;
	Arena* arena = Malloc(totalSize);
	Memset(arena, 0, totalSize);
	arena->size = size;
	return arena;
}

void* ArenaAlloc(Arena* arena, const uSize size) {
	if (arena->used + size > arena->size) { return null; }
	const uPtr ptr = (uPtr)(arena->data + arena->used);
	arena->used += size;
	return (u8*)ptr;
}

void ArenaReset(Arena* arena) {
	arena->used = 0;
}

void ArenaFree(Arena* arena) {
	Free(arena, sizeof(Arena) + arena->size);
}

u64 ArenaRemaining(const Arena* arena) {
	return arena->size - arena->used;
}

u64 ArenaSize(const Arena* arena) {
	return arena->size;
}