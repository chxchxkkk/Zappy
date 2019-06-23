/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

bool cmd_tna(zappy_server_t *server, player_t *player, UNUSED char *const *args)
{
    for (size_t i = 0 ; i < server->settings.nb_teams ; ++i)
        client_reply(player->client.fd, "tna %s\n", server->settings.team_names[i]);
    return (true);
}
