/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

void list_delete_node(list_t **begin, list_t *node, list_del_t del)
{
    list_t *prev = node->prev;
    list_t *next = node->next;

    if (prev != NULL)
        prev->next = next;
    else
        *begin = next;
    if (next != NULL)
        next->prev = prev;
    if (del != NULL)
        del(node);
}
