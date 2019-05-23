/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

list_t *list_create_node(size_t size)
{
    list_t *node = malloc(size);

    if (node == NULL)
        return (NULL);
    node->prev = NULL;
    node->next = NULL;
    return (node);
}
