/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include <malloc.h>

char *str_join(const char *delim, char *const *array)
{
    size_t delimsize = strlen(delim);
    size_t size = 0;
    char *str;

    for (size_t i = 0 ; array[i] != NULL ; ++i)
        size += strlen(array[i]) + delimsize;
    size = size - delimsize + 1;
    str = calloc(size, sizeof(char));
    if (str == NULL)
        return (NULL);
    for (size_t i = 0 ; array[i] != NULL ; ++i) {
        strcat(str, array[i]);
        if (array[i + 1] != NULL)
            strcat(str, delim);
    }
    return (str);
}