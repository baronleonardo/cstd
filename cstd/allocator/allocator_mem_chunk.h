#ifndef ALLOCATOR_MEM_CHUNCK_H
#define ALLOCATOR_MEM_CHUNCK_H

#include "../def.h"

typedef struct {
    void* mem;
    size_t size;
} Allocator_Mem_Chunk;

#endif // ALLOCATOR_MEM_CHUNCK_H