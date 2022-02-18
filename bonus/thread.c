/*
** EPITECH PROJECT, 2021
** my_malloc [WSL: Ubuntu]
** File description:
** thread
*/

#include <pthread.h>
#include "my_malloc.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size)
{
    void *ptr = NULL;

    pthread_exec(mutex, ptr, my_malloc, size);
    return (ptr);
}

void *realloc(void *ptr, size_t size)
{
    pthread_exec(mutex, ptr, my_realloc, ptr, size);
    return (ptr);
}

void *calloc(size_t nb, size_t size)
{
    void *ptr = NULL;

    pthread_exec(mutex, ptr, my_calloc, nb, size);
    return (ptr);
}

void free(void *ptr)
{
    pthread_mutex_lock(&mutex);
    my_free(ptr);
    pthread_mutex_unlock(&mutex);
}