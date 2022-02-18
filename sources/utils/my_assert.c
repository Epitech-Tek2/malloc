/*
** EPITECH PROJECT, 2021
** my_malloc [WSL: Ubuntu]
** File description:
** my_assert
*/

#include <stdio.h>
#include "my_malloc.h"

static size_t my_strlen(char const *restrict string)
{
    size_t i = 0;

    if (!string) return (0);
    for (i = 0; string[i]; i++);
    return (i);
}

void my_assert_fail(char const *restrict message)
{
    size_t length = my_strlen(message);

    if (!length) exit(84);
    write(2, message, length);
    exit(84);
}