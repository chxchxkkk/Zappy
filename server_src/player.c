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

void free_player(player_t *player)
{
    free_client(&player->client);
    for (size_t i = 0 ; i < ARRAY_LEN(player->commands) ; ++i)
        free(player->commands[i]);
}
