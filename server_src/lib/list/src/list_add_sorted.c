/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

list_t *list_add_sorted(list_t **begin, list_t *node, list_cmp_t cmp)
{
    if (*begin == NULL || cmp(node, (*begin)) <= 0)
        return (list_push(begin, node));
    for (list_t *tmp = (*begin)->next ; tmp != NULL ; tmp = tmp->next)
        if (cmp(node, tmp) <= 0)
            return (list_insert(tmp->prev, node));
    return (list_append(begin, node));
}
