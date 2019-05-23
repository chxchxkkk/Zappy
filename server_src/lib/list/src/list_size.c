/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#include "list.h"

size_t list_size(list_t const *begin)
{
    for (size_t i = 0 ;; i++) {
        if (begin == NULL)
            return (i);
        begin = begin->next;
    }
}
