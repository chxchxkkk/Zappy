/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

list_t *list_find_node(list_t *list, const list_t *node, list_cmp_t cmp)
{
    for (list_t *tmp = list ; tmp != NULL ; tmp = tmp->next)
        if (cmp(node, tmp) == 0)
            return (tmp);
    return (NULL);
}
