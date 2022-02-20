#ifndef ARENA_H
#define ARENA_H

#include "../def.h"
#include "allocator_mem_chunk.h"

typedef struct {
    u8* mem;
    size_t mem_len;
    size_t cur_chunck_start;
    size_t cur_chunck_end;
    bool valid;
} Allocator_Arena;

Allocator_Arena
allocator_arena_create(size_t size);

Allocator_Mem_Chunk
allocator_arena_alloc_aligned(Allocator_Arena* self, size_t size, size_t align);

/*
 * same like `allocator_arena_alloc_aligned` but using
 * the `DEFAULT_ALIGNMENT` macro from `config.h`
 */
Allocator_Mem_Chunk
allocator_arena_alloc(Allocator_Arena* self, size_t size);

Allocator_Mem_Chunk
allocator_arena_resize_aligned(
    Allocator_Arena* self,
    Allocator_Mem_Chunk old_memory,
    size_t new_size,
    size_t align
);

/*
 * same like `allocator_arena_resize_aligned` but using
 * the `DEFAULT_ALIGNMENT` macro from `config.h`
 */
Allocator_Mem_Chunk
allocator_arena_resize(
    Allocator_Arena* self,
    Allocator_Mem_Chunk old_memory,
    size_t new_size
);

void
allocator_arena_destroy(Allocator_Arena* self);

#endif // ARENA_H