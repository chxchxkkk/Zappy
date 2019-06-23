/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_ppo(zappy_server_t *server, player_t *player, char *const *args)
{
    unsigned int id = (unsigned int)strtoul(args[1], NULL, 10);
    player_t *actual = LIST_FIND(server->player_list,
        it->state == PLAYER_DEFAULT && (unsigned int)it->id == id);

    if (actual == NULL) {
        client_reply(player->client.fd, "sbp\n");
        return (false);
    }
    client_reply(player->client.fd, "ppo %d %d %d %d\n", actual->id,
        actual->position.x, actual->position.y, actual->direction);
    return (true);
}
