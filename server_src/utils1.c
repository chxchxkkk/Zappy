/*
** EPITECH PROJECT, 2019
** myARPspoof
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include <unistd.h>
#include "utils.h"

void *memdup(const void *src, size_t n)
{
    void *buf = malloc(n);

    if (buf == NULL)
        return (NULL);
    return (memcpy(buf, src, n));
}

void clean_close(const int *fd_ptr)
{
    close(*fd_ptr);
}

void clean_ptr(void *ptr)
{
    free(*(void **)ptr);
    *(void **)ptr = NULL;
}

void clean_strarr(char ***arrayp)
{
    char **array = *arrayp;

    if (array == NULL)
        return;
    for (size_t i = 0 ; array[i] != NULL ; ++i)
        free(array[i]);
    free(array);
}

float randf(void)
{
    return (float)((double)rand() / (double)RAND_MAX);
}
