/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include "zappy.h"

void update_game(zappy_server_t *server)
{
    LIST_FOREACH(player, server->player_list, {
        update_player(server, player);
    });
}
