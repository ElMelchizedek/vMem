#include "vmem.h"
#include <stdlib.h>
#include <string.h>

Arena Arena_Init(size_t size) {
    const Arena arena = {
        .memory = malloc(size),
        .size = size,
        .offset = 0,
    };

    return arena;
}

void Arena_Free(Arena* arena) {
    free(arena->memory);
    arena->memory = NULL;
    arena->offset = 0;
    arena->size = 0;
}

void* Arena_Push(Arena* arena, size_t size) {
    if ( (arena->offset + size) > arena->size ) {
        return NULL; // Out of memory.
    }

    void* ptr = arena->memory + arena->offset;
    arena->offset += size;
    return ptr;
}

bool Arena_Pop(Arena* arena, size_t size) {
    if ( (arena->offset - size) < 0 ) {
        return false; // Would result in negative size.
    }
    arena->offset -= size;
    return true;
}

bool Arena_Expand(Arena* arena) {
    const size_t new_size = arena->size * 2;
    uint8_t* new_memory = malloc(new_size);
    if (!new_memory) {
        return false; // Allocation failure.
    }
    memcpy(new_memory, arena->memory, arena->size);

    free(arena->memory);
    arena->memory = new_memory;
    arena->size = new_size;
    return true;
}
