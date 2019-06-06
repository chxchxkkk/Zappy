/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

int list_delete_matching_nodes(list_t **begin, list_match_t match,
    list_del_t del, ...)
{
    va_list ap;
    va_list cpy;
    list_t *tmp = *begin;
    int num = 0;

    va_start(ap, del);
    while (tmp != NULL) {
        va_copy(cpy, ap);
        if (match(tmp, &cpy)) {
            list_delete_node(begin, tmp, del);
            tmp = *begin;
            num++;
        } else
            tmp = tmp->next;
        va_end(cpy);
    }
    va_end(ap);
    return (num);
}
