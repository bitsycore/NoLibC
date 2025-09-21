#include "public/nlc_arena.h"

#include "public/nlc_memory.h"

typedef struct Arena {
	uSize size;
	uSize used;
	u8 data[];
} Arena;

Arena* ArenaNew(const uSize size) {
	const uSize totalSize = sizeof(Arena) + size;
	Arena* arena = MemoryPageAlloc(totalSize);
	MemorySet(arena, 0, totalSize);
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
	MemoryPageFree(arena, sizeof(Arena) + arena->size);
}

uSize ArenaRemaining(const Arena* arena) {
	return arena->size - arena->used;
}

uSize ArenaSize(const Arena* arena) {
	return arena->size;
}