/*
** EPITECH PROJECT, 2021
** B-PSU-400-STG-4-1-malloc-clement.muth [WSL: Ubuntu]
** File description:
** structure
*/

#pragma once

#include "my_malloc.h"

typedef struct chunk_s
{
    size_t is_free;
    size_t size;
    struct chunk_s *next;
    struct chunk_s *prev;
    void *data;
} chunk_t;

typedef struct heap_s
{
    chunk_t *first;
    chunk_t *last;
    size_t page;
    void *breakptr;
} heap_t;