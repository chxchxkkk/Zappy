/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_connect_nbr(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    client_reply(player->client.fd, "%ld\n",
        server->clients_limits[player->team_id]);
    return (true);
}
