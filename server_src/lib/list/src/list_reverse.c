/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

void list_reverse(list_t **begin)
{
    list_t *list = *begin;
    list_t *last = list_getlast(list);
    size_t size = list_size(list);

    if (last == NULL)
        return;
    for (size_t i = 0 ; i < size / 2 ; i++) {
        list_swap_nodes(begin, list, last);
        list = list->next;
        last = last->prev;
    }
}