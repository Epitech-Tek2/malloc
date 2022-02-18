/*
** EPITECH PROJECT, 2021
** my_malloc-master [WSL: Ubuntu]
** File description:
** macro
*/

#pragma once

#include "my_malloc.h"

#define init_heap(chunk, page_size, i, heap) ({ \
    heap = sbrk((intptr_t)((void *)heap + page_size * i)); \
    heap->page = page_size; \
    heap->breakptr = (void *)heap + page_size * i; \
    heap->last = (void *)heap + SIZE_HEAP; \
    chunk = (chunk_t *)((void *)heap + SIZE_HEAP); \
    heap->first = chunk; \
})

#define init_chunk(chunk, page_size, i, heap) ({ \
    chunk->size = page_size * i - SIZE_HEAP - SIZE_CHUNK; \
    chunk->is_free = true; \
    chunk->prev = NULL; \
    chunk->next = heap->breakptr; \
    chunk->data = (void *)chunk + SIZE_CHUNK; \
})

#define init_memory(chunk, page_size, i, heap) ({ \
    init_heap(chunk, page_size, i, heap); \
    init_chunk(chunk, page_size, i, heap); \
})

#define chunk_split(chunk_split, chunk, size) ({ \
    chunk_split = (chunk_t *)(ptr + SIZE_CHUNK + size); \
    chunk_split->size = chunk->size - (size + SIZE_CHUNK); \
    chunk_split->is_free = true; \
    chunk_split->next = chunk->next; \
    chunk_split->prev = chunk; \
    chunk_split->data = (void *)chunk_split + SIZE_CHUNK; \
    chunk->size = size; \
})

#define update_chunk(chunk) ({ \
    chunk->size = PAGE_I - SIZE_CHUNK; \
    chunk->is_free = true; \
    chunk->next = heap->breakptr; \
    chunk->prev = heap->last; \
    chunk->data = (void *)chunk + SIZE_CHUNK; \
})

#define my_assert(expr, message) ((void)sizeof((expr) ? 1 : 0), \
__extension__({ \
    if (expr); /* empty */ \
    else my_assert_fail(message); \
}))

#define pthread_exec(mutex, ptr, func, ...) ({ \
    pthread_mutex_lock(&mutex); \
    ptr = func(__VA_ARGS__); \
    pthread_mutex_unlock(&mutex); \
})

#define is_between(ma, mi) ((size <= ma && size > mi) ? (true) : (false))
