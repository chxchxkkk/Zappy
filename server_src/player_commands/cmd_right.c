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

bool cmd_right(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    player->direction = player->direction % 4 + 1;
    client_reply(player->client.fd, "ok\n");
    notify_graphic(server, "ppo %d %d %d %d\n", player->id, player->position.x,
        player->position.y, player->direction);
    return (true);
}
