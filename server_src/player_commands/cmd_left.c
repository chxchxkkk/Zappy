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

bool cmd_left(UNUSED zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    player->direction = (player->direction - 2) % 4 + 1;
    dprintf(player->client.fd, "ok\n");
    return (true);
}
