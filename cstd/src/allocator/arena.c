#include "../../allocator/arena.h"
#include "../../config.h"
#include "__arena__.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

Allocator_Arena
allocator_arena_create(size_t size)
{
    Allocator_Arena arena = {};

    arena.mem = malloc(size);
    if(!arena.mem)
    {
        return arena;
    }

    arena.cur_chunck_start = arena.cur_chunck_end = 0;
    arena.mem_len = size;

    arena.valid = true;
    return arena;
}

Allocator_Mem_Chunk
allocator_arena_alloc_aligned(Allocator_Arena* self, size_t size, size_t align)
{
    if(!self || !self->valid)
    {
        return (Allocator_Mem_Chunk){ NULL, 0 };
    }

    // Align 'curr_offset' forward to the specified alignment
    uptr cur_pos = (uptr)(self->mem + self->cur_chunck_end);
    size_t offset = __forward_align__(cur_pos, align);
    offset -= (uptr)self->mem; // Change to relative offset

    // check if there is space left
    if(offset + size <= self->mem_len)
    {
        void* ptr = &self->mem[self->cur_chunck_end];
        self->cur_chunck_start = offset;
        self->cur_chunck_end = offset + size;

        // Zero new memory by default
        memset(ptr, 0, size);
        return (Allocator_Mem_Chunk) { ptr, size };
    }

    return (Allocator_Mem_Chunk){ NULL, 0 };
}

Allocator_Mem_Chunk
allocator_arena_alloc(Allocator_Arena* self, size_t size)
{
    return allocator_arena_alloc_aligned(self, size, DEFAULT_ALIGNMENT);
}

Allocator_Mem_Chunk
allocator_arena_resize_aligned(Allocator_Arena* self, Allocator_Mem_Chunk old_memory, size_t new_size, size_t align)
{
    if(!self || !self->valid)
    {
        return (Allocator_Mem_Chunk){ NULL, 0 };
    }

    // empty old_memory -> reserve new memory chunck
    if(old_memory.mem == NULL || old_memory.size == 0)
    {
        return allocator_arena_alloc_aligned(self, new_size, align);
    }
    // if the old_memory location is within out arena
    else if(((u8 *)old_memory.mem >= self->mem) && 
            ((u8 *)old_memory.mem < (self->mem + self->mem_len))
           )
    {
        // if old_memory is the last one in our arena
        if(old_memory.mem == (self->mem + self->cur_chunck_start))
        {
            if(new_size > old_memory.size)
            {
                memset(&self->mem[self->cur_chunck_end], 0, new_size - old_memory.size);
            }

            self->cur_chunck_end = self->cur_chunck_start + new_size;
        }
        else
        {
            Allocator_Mem_Chunk new_mem_chunck = allocator_arena_alloc_aligned(self, new_size, align);
            new_mem_chunck.size = new_size;
            size_t mem_size_to_move = old_memory.size < new_size ? old_memory.size : new_size;
            memmove(new_mem_chunck.mem, old_memory.mem, mem_size_to_move);

            return new_mem_chunck;
        }
    }
    else
    {
        assert(false && "Memory is out of boundry from this arena");
    }
}

Allocator_Mem_Chunk
allocator_arena_resize(Allocator_Arena* self, Allocator_Mem_Chunk old_memory, size_t new_size)
{
    return allocator_arena_resize_aligned(self, old_memory, new_size, DEFAULT_ALIGNMENT);
}

void
allocator_arena_destroy(Allocator_Arena* self)
{
    if(self)
    {
        free(self->mem);
        *self = (Allocator_Arena){};
    }
}