/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

int list_apply_on_matching_nodes(list_t *list, list_apply_t func,
    const list_t *node, list_cmp_t cmp)
{
    int result = 0;

    while (list != NULL) {
        if (cmp(node, list) == 0)
            result += func(list);
        list = list->next;
    }
    return (result);
}
