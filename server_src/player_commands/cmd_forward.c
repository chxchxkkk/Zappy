/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_forward(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    player_move(server, player, DIRECTIONS[player->direction].x,
        DIRECTIONS[player->direction].y);
    client_reply(player->client.fd, "ok\n");
    return (true);
}
