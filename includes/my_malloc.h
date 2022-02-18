/*
** EPITECH PROJECT, 2021
** my_malloc [WSL: Ubuntu]
** File description:
** malloc
*/

#pragma once

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <features.h>
#include <stddef.h>
#include <stdbool.h>
#include <malloc.h>
#include "macro.h"
#include "define.h"
#include "functions.h"
#include "structure.h"

extern void *my_malloc(size_t size);

extern void my_free(register void const *restrict ptr);
chunk_t *get_first_free(chunk_t *chunk);

extern void *my_realloc(void *ptr, size_t size);

extern void *my_calloc(size_t nb, size_t size);

chunk_t *alloc_chunk(chunk_t *chunk, register size_t const size);

/* Allocate SIZE bytes of memory. */
extern void *malloc(size_t size) __attribute_malloc__
    __attribute_alloc_size__ ((1)) __wur;

/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0. */
extern void *calloc(size_t nmemb, size_t size)
    __attribute_malloc__ __attribute_alloc_size__ ((1, 2)) __wur;

/* __attribute_malloc__ is not used, because if realloc returns
    the same pointer that was passed to it, aliasing needs to be allowed
   is_between objects pointed by the old and new pointers. */

/* Re-allocate the previously allocated block in ptr, making the new
    block SIZE bytes long. */
extern void *realloc(void *ptr, size_t size)
    __attribute_warn_unused_result__ __attribute_alloc_size__ ((2));

/* __attribute_malloc__ is not used, because if reallocarray returns
    the same pointer that was passed to it, aliasing needs to be allowed
    is_between objects pointed by the old and new pointers. */

/* Re-allocate the previously allocated block in PTR, making the new
   block large enough for NMEMB elements of SIZE bytes each. */
extern void *reallocarray(void *ptr, size_t nmemb, size_t size)
    __attribute_warn_unused_result__ __attribute_alloc_size__ ((2, 3));

#include "inline.h"