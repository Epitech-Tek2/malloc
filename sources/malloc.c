/*
** EPITECH PROJECT, 2021
** my_malloc-master [WSL: Ubuntu]
** File description:
** malloc
*/

#include "my_malloc.h"

heap_t *heap = NULL;

chunk_t *alloc_chunk(chunk_t *chunk, register size_t const size)
{
    chunk_t *chunk_splite = NULL;
    void *ptr = (void *)chunk;

    if (chunk->size >= size + ALIGN_NSIZE) {
        chunk_split(chunk_splite, chunk, size);
        if (chunk->next != heap->breakptr) chunk->next->prev = chunk_splite;
        chunk->next = chunk_splite;
        heap->last = (heap->last == chunk) ? chunk_splite : heap->last;
        heap->first = (heap->first == chunk) ? chunk_splite : heap->first;
    }
    chunk->is_free = false;
    chunk->data = (void *)chunk + SIZE_CHUNK;
    if (chunk == heap->first) heap->first = get_first_free(chunk);
    return (chunk);
}

static chunk_t *init_heap_memory(register size_t const size)
{
    register size_t const page_size = getpagesize() * 2;
    register size_t i = 1;
    chunk_t *chunk = NULL;

    while ((page_size * i) < (SIZE_HEAP + SIZE_CHUNK + size) && (i++));
    init_memory(chunk, page_size, i, heap);
    return (alloc_chunk(chunk, size));
}

static bool new_page(register size_t const size)
{
    chunk_t *chunk = NULL;
    int i = 1;

    while (PAGE_I < SIZE_CHUNK + size && (i++));
    chunk = (chunk_t *)heap->breakptr;
    heap->breakptr += PAGE_I;
    if (brk(heap->breakptr)) return (false);
    update_chunk(chunk);
    heap->last = chunk;
    return (true);
}

static chunk_t *find_chunk(register size_t const size)
{
    chunk_t *chunk = NULL;

    if (!heap->first)
        return (!(new_page(size))) ? (NULL) : (alloc_chunk(heap->first, size));
    chunk = heap->first;
    for (; chunk != heap->breakptr; chunk = chunk->next)
        if (chunk->size >= (size) && chunk->is_free)
            return (alloc_chunk(chunk, size));
    if (!(new_page(size))) return (NULL);
    return (heap->last->prev->is_free) ?
    (alloc_chunk(merge_chunk(heap->last->prev), size)) :
    (alloc_chunk(heap->last, size));
}

void *my_malloc(register size_t size)
{
    chunk_t *chunk = NULL;

    if (0 == size) return (NULL);
    size = (size < 42 - SIZE_CHUNK && 1 != size) ? (42 - SIZE_CHUNK) : (size);
    size = align_malloc(size);
    chunk = (!heap) ? init_heap_memory(size) : find_chunk(size);
    return (chunk) ? ((void *)chunk + SIZE_CHUNK) : (NULL);
}