/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include "utils.h"
#include "map.h"
#include "game_objects.h"

static void generate_cell(cell_t *cell, float ratio)
{
    for (size_t i = 0 ; i < ARRAY_LEN(RARITIES) ; ++i)
        for (size_t j = 0 ; j < (size_t)(RARITIES[i].max * ratio) ; ++j)
            if (randf() / ratio <= RARITIES[i].rarity)
                cell->objects[RARITIES[i].resource]++;
}

map_t *generate_map(size_t width, size_t height, float ratio)
{
    map_t map = {
        .width = width, .height = height,
        .cells = calloc(width, sizeof(cell_t)),
    };

    if (map.cells == NULL)
        return (NULL);
    for (size_t x = 0 ; x < width ; ++x) {
        map.cells[x] = calloc(height, sizeof(cell_t));
        if (map.cells[x] == NULL)
            return (NULL);
        for (size_t y = 0 ; y < height ; ++y)
            generate_cell(&map.cells[x][y], ratio);
    }
    return (memdup(&map, sizeof(map)));
}

cell_t *get_cell(map_t *map, size_t x, size_t y)
{
    return &map->cells[x % map->width][y % map->height];
}

void free_map(map_t *map)
{
    for (size_t x = 0 ; x < map->width ; ++x)
        free(map->cells[x]);
    free(map->cells);
    free(map);
}
