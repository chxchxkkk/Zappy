/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

static void sort_swap(list_t **begin, list_t *a, list_t *b, list_cmp_t cmp)
{
    if (cmp(a, b) > 0)
        list_swap_nodes(begin, a, b);
}

void list_sort(list_t **begin, list_cmp_t cmp)
{
    size_t len = list_size(*begin);

    for (size_t i = 0 ; i < len ; i++)
        for (list_t *j = (*begin)->next ; j != NULL ; j = j->next)
            sort_swap(begin, j->prev, j, cmp);
}
