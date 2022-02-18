/*
** EPITECH PROJECT, 2021
** my_malloc [WSL: Ubuntu]
** File description:
** define
*/

#include <malloc.h>

#pragma once

#define PAGE_I heap->page * i

#define SIZE_HEAP sizeof(heap_t)

#define SIZE_CHUNK sizeof(chunk_t)

#define ALIGN_NSIZE SIZE_CHUNK + 42 - SIZE_CHUNK

#define TOTAL_SIZE_CHUNK chunk->size + sizeof(chunk_t)

#define HEAP_LAST_NEXT \
    heap->first = (chunk2 == heap->first) ? chunk : heap->first; \
    heap->last = (chunk2 == heap->last) ? chunk : heap->last;

#define INVALID_PTR "free(): invalid pointer\n"