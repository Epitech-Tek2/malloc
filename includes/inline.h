/*
** EPITECH PROJECT, 2021
** my_malloc [WSL: Ubuntu]
** File description:
** inline
*/

#pragma once

#include <errno.h>
#include "my_malloc.h"

extern heap_t *heap;

__always_inline static inline chunk_t *merge_chunk(chunk_t *chunk)
{
    chunk_t *chunk2 = chunk->next;

    chunk->size += SIZE_CHUNK + chunk2->size;
    chunk->next = chunk2->next;
    if (chunk2->next != heap->breakptr) chunk2->next->prev = chunk;
    HEAP_LAST_NEXT;
    return (chunk);
}

__always_inline static inline void *realloc_chunk(chunk_t *chunk, size_t size)
{
    return ((void *)alloc_chunk(chunk, size) + SIZE_CHUNK);
}

__always_inline static inline void *realloc_block(chunk_t *chunk, size_t size)
{
    void *ptr = my_malloc(size);

    memcpy(ptr, (void *)chunk + SIZE_CHUNK, chunk->size);
    my_free((void *)chunk + SIZE_CHUNK);
    return (ptr);
}

__always_inline static inline size_t align_malloc(register size_t const size)
{
    register size_t b = 0x4000000000000000;

    if (1 == size) return (1);
    if ((size & (size - 1)) == 0) return (size);
    while (b >>= 1)
        if (size & b) return ((0 | b) << 1);
    return (1);
}