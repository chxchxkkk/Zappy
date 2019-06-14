/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include <assert.h>
#include "utils.h"
#include "zappy.h"

static const position_t DIRECTIONS[] = {
    [NORTH] = {1, 1},
    [EAST] = {1, -1},
    [SOUTH] = {-1, -1},
    [WEST] = {-1, 1},
};

cell_t **get_vision_cells(const map_t *map, const player_t *player)
{
    size_t i = 0;
    size_t size = (player->level + 1) * (player->level + 1);
    cell_t *cells[size + 1];

    for (int y = 0 ; y <= (int)player->level ; ++y)
        for (int x = -y ; x <= y ; ++x)
            if (player->direction % 2 == 0)
                cells[i++] = get_cell(map,
                    player->position.x + DIRECTIONS[player->direction].x * y,
                    player->position.y + DIRECTIONS[player->direction].y * x);
            else
                cells[i++] = get_cell(map,
                    player->position.x + DIRECTIONS[player->direction].x * x,
                    player->position.y + DIRECTIONS[player->direction].y * y);
    cells[size] = NULL;
    return (memdup(cells, sizeof(cells)));
}
