/*
** EPITECH PROJECT, 2021
** my_malloc [WSL: Ubuntu]
** File description:
** realloc
*/

#include "my_malloc.h"

extern heap_t *heap;

void *my_calloc(size_t nb, size_t size)
{
    void *ptr = NULL;

    if (!nb || !size) return (NULL);
    ptr = my_malloc(nb * size);
    memset(ptr, 0, nb * size);
    return (ptr);
}

void *my_realloc(void *ptr, size_t size)
{
    chunk_t *chunk = NULL;

    if (!ptr) return (my_malloc(size));
    if (!size) {
        my_free(ptr);
        return (NULL);
    }
    if (heap == NULL) return (my_malloc(size));
    if (ptr < (void *)heap || ptr > heap->breakptr) return (NULL);
    chunk = (chunk_t *)(ptr - SIZE_CHUNK);
    if (chunk->data != (void *)chunk + SIZE_CHUNK) return (NULL);
    if (size <= chunk->size) return (realloc_chunk(chunk, size));
    return (realloc_block(chunk, size));
}