/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

list_t *list_insert(list_t *prev, list_t *node)
{
    list_t *next = prev->next;

    if (node == NULL)
        return (NULL);
    node->next = next;
    node->prev = prev;
    prev->next = node;
    if (next != NULL)
        next->prev = node;
    return (node);
}
