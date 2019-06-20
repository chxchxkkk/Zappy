/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_sgt(zappy_server_t *server, player_t *player, UNUSED char *const *args)
{
    client_reply(player->client.fd, "sgt %d\n", server->settings.freq);
    return (true);
}
