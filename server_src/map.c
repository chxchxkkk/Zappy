/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "utils.h"
#include "map.h"
#include "game_objects.h"

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

void free_map(map_t *map)
{
    for (size_t x = 0 ; x < map->width ; ++x)
        free(map->cells[x]);
    free(map->cells);
    free(map);
}

void map_info(const map_t *map)
{
    int resources[NB_GAME_OBJECTS] = {0};

    for (size_t x = 0 ; x < map->width ; ++x)
        for (size_t y = 0 ; y < map->height ; ++y)
            for (size_t i = 0 ; i < NB_GAME_OBJECTS ; ++i)
                resources[i] += get_cell(map, x, y)->objects[i];
    for (size_t i = 0 ; i < NB_GAME_OBJECTS ; ++i)
        printf("%s: %d\n", OBJ_NAMES[i], resources[i]);
}
