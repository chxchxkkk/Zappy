/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <stddef.h>
#include "game_objects.h"

typedef struct cell {
    unsigned int objects[NB_GAME_OBJECTS];
} cell_t;

typedef struct map {
    cell_t **cells;
    size_t width;
    size_t height;
} map_t;

void free_map(map_t *map);
cell_t *get_cell(map_t *map, size_t x, size_t y);
map_t *generate_map(size_t width, size_t height, float ratio);
