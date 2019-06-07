/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "map.h"

void generate_cell(cell_t *cell, float ratio)
{
    for (size_t i = 0 ; i < ARRAY_LEN(RARITIES) ; ++i)
        for (size_t j = 0 ; j < (size_t)(RARITIES[i].max) ; ++j)
            if (randf() / ratio <= RARITIES[i].rarity)
                cell->objects[RARITIES[i].resource]++;
}

cell_t *get_cell(const map_t *map, int x, int y)
{
    return &map->cells[x % map->width][y % map->height];
}
