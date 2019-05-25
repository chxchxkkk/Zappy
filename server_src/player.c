/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <unistd.h>
#include <stdio.h>
#include "utils.h"
#include "player.h"

const int ELEVATION_CHART[MAX_LEVEL][NB_GAME_OBJECTS] = {
    [0] = {0},
    /* player food linemate deraumere sibur mendiane phiras thystame */
    [1] = {1, 0, 1, 0, 0, 0, 0, 0},
    [2] = {2, 0, 1, 1, 1, 0, 0, 0},
    [3] = {2, 0, 2, 0, 1, 0, 2, 0},
    [4] = {4, 0, 1, 1, 2, 0, 1, 0},
    [5] = {4, 0, 1, 2, 1, 3, 0, 0},
    [6] = {6, 0, 1, 2, 3, 0, 1, 0},
    [7] = {6, 0, 2, 2, 2, 2, 2, 1},
};

void free_player(player_t *player)
{
    free_client(&player->client);
    for (size_t i = 0 ; i < ARRAY_LEN(player->commands) ; ++i)
        free(player->commands[i]);
}
