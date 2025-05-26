#ifndef VMEM_H
#define VMEM_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MEGABYTE (1024 * 1024)

typedef struct {
  uint8_t* memory;
  size_t size;
  size_t offset;
} Arena;

Arena Arena_Init(size_t size);
void Arena_Free(Arena* arena);
void* Arena_Push(Arena* arena, size_t size);
bool Arena_Pop(Arena* arena, size_t size);
bool Arena_Expand(Arena* arena);

#endif // VMEM_H
