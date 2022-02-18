/*
** EPITECH PROJECT, 2021
** my_malloc [WSL: Ubuntu]
** File description:
** free
*/

#include "my_malloc.h"

extern heap_t *heap;

static void check_page(void)
{
    chunk_t *chunk = heap->last;
    size_t page_delete = (TOTAL_SIZE_CHUNK) / heap->page;
    size_t size_rest = (TOTAL_SIZE_CHUNK) % heap->page;

    if (TOTAL_SIZE_CHUNK >= heap->page) {
        if (size_rest >= ALIGN_NSIZE) chunk->size = size_rest - SIZE_CHUNK;
        else if (0 == size_rest) heap->last = chunk->prev;
        else {
            heap->last = chunk->prev;
            heap->last->size += size_rest - SIZE_CHUNK;
        }
        heap->breakptr -= page_delete * heap->page;
        heap->last->next = heap->breakptr;
        brk(heap->breakptr);
    }
}

void my_free(register void const *restrict ptr)
{
    chunk_t *chunk = NULL;

    if (!ptr || ptr < (void *)heap || ptr >= heap->breakptr) return;
    chunk = (chunk_t *)(ptr - SIZE_CHUNK);
    if (chunk->data != (void *)chunk + SIZE_CHUNK || chunk->is_free) return;
    chunk->is_free = true;
    if (chunk->prev && chunk->prev->is_free) {
        chunk = chunk->prev;
        merge_chunk(chunk);
    }
    if (chunk->next != heap->breakptr && chunk->next->is_free)
        merge_chunk(chunk);
    if (ptr < (void *)heap->first) heap->first = chunk;
    if (ptr - SIZE_CHUNK == (void *)heap->last) check_page();
}

chunk_t *get_first_free(chunk_t *chunk)
{
    for (; chunk != heap->breakptr; chunk = chunk->next)
        if (chunk->is_free) break;
    return (chunk);
}