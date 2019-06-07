/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_msz(zappy_server_t *server, player_t *player, UNUSED char *const *args)
{
    dprintf(player->client.fd, "msz %ld %ld\n", server->map->width,
        server->map->height);
    return (true);
}
