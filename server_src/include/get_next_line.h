/*
** EPITECH PROJECT, 2017
** GetNextLine
** File description:
** Created by antoine_dh,
*/

#ifndef GETNEXTLINE_GET_NEXT_LINE_H
#define GETNEXTLINE_GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef READ_SIZE
#define READ_SIZE    (4096)
#endif

char *get_next_line(int fd);

#endif //GETNEXTLINE_GET_NEXT_LINE_H
