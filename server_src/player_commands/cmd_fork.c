/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_fork(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    if (lay_egg(server, player) == NULL) {
        client_reply(player->client.fd, "ko\n");
        return (false);
    }
    client_reply(player->client.fd, "ok\n");
    return (true);
}
