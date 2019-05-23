/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

static void swap_adjacent(list_t *a, list_t *b)
{
    list_t *left = a->prev == b ? b : a;
    list_t *right = a->prev == b ? a : b;
    list_t *tmp = left->prev;

    left->next = right->next;
    left->prev = right;
    right->prev = tmp;
    right->next = left;
    if (left->next != NULL)
        left->next->prev = left;
    if (right->prev != NULL)
        right->prev->next = right;
}

void list_swap_nodes(list_t **begin, list_t *a, list_t *b)
{
    list_t tmp = {.prev = a->prev, .next = a->next};

    if (a == b)
        return;
    if (a == *begin || b == *begin)
        *begin = (a == *begin) ? b : a;
    if (a->prev == b || a->next == b)
        return swap_adjacent(a, b);
    if (a->prev != NULL)
        a->prev->next = b;
    if (a->next != NULL)
        a->next->prev = b;
    a->next = b->next;
    a->prev = b->prev;
    if (b->prev != NULL)
        b->prev->next = a;
    if (b->next != NULL)
        b->next->prev = a;
    b->next = tmp.next;
    b->prev = tmp.prev;
}
