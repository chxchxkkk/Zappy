/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

list_t *list_getlast(list_t *begin)
{
    list_t *tmp = begin;

    if (begin == NULL)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}
