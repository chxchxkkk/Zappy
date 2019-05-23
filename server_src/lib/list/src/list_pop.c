/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

void *list_pop(list_t **begin)
{
    list_t *last = list_getlast(*begin);

    if (last == NULL)
        return (NULL);
    if (last->prev != NULL)
        last->prev->next = NULL;
    else
        *begin = NULL;
    last->prev = NULL;
    return (last);
}
