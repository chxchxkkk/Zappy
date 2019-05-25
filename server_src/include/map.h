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
map_t *generate_map(size_t width, size_t height, float ratio);
void map_info(const map_t *map);

cell_t *get_cell(const map_t *map, size_t x, size_t y);
void print_cell(const cell_t *cell);
void generate_cell(cell_t *cell, float ratio);
