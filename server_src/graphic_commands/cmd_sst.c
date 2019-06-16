/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_sst(zappy_server_t *server, player_t *player, char *const *args)
{
    unsigned int t = (unsigned int)strtoul(args[1], NULL, 10);

    if (t == UINT32_MAX || t == 0) {
        dprintf(player->client.fd, "sbp\n");
        return (false);
    }
    server->settings.freq = t;
    dprintf(player->client.fd, "sgt %d\n", server->settings.freq);
    return (true);
}
