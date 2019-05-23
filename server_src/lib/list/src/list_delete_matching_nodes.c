/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

int list_delete_matching_nodes(list_t **begin, const list_t *node,
    list_cmp_t cmp, list_del_t del)
{
    list_t *tmp = *begin;
    int num = 0;

    while (tmp != NULL) {
        if (cmp(node, tmp) == 0) {
            list_delete_node(begin, tmp, del);
            tmp = *begin;
            num++;
        } else
            tmp = tmp->next;
    }
    return (num);
}
