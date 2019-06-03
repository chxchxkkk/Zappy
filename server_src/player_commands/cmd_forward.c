/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <zappy.h>
#include "utils.h"
#include "commands.h"

static const position_t DIRECTIONS[] = {
    [NORTH] = {0, 1},
    [EAST] = {1, 0},
    [SOUTH] = {0, -1},
    [WEST] = {-1, 0},
};

bool cmd_forward(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER] -= 1;
    player->position.x += DIRECTIONS[player->direction].x;
    player->position.y += DIRECTIONS[player->direction].y;
    player->position.x %= server->map->width;
    player->position.y %= server->map->height;
    get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER] += 1;
    dprintf(player->client.fd, "ok\n");
    return (true);
}
