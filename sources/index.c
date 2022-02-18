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

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if ((nmemb >= ((size_t)1 << (sizeof(size_t) * 4)) ||
        size >= ((size_t)1 << (sizeof(size_t) * 4))) &&
        nmemb > 0 && (18446744073709551615UL) / nmemb < size) {
        (*__errno_location ()) = 12;
        return ((void *)0);
    }
    return (realloc(ptr, size * nmemb));
}
