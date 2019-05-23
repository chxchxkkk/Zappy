/*
** EPITECH PROJECT, 2019
** myftp
** File description:
** Created by antoine_dh,
*/

#include "list.h"

list_t *list_at(list_t *begin, size_t idx)
{
    list_t *node;

    for (node = begin ; node != NULL && idx != 0 ; node = node->next)
        idx--;
    return (node);
}
