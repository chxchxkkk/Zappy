/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

static void eject_player(zappy_server_t *server, player_t *ejecter,
    player_t *ejected)
{
    player_move(server, ejected, DIRECTIONS[ejecter->direction].x,
        DIRECTIONS[ejecter->direction].y);
    dprintf(ejected->client.fd, "ejected: %d\n",
        get_sound_direction(server->map, &ejecter->position, &ejected->position,
            ejected->direction));
}

bool cmd_eject(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    bool ok = false;

    LIST_FOREACH(p, server->player_list, {
        if (p->state == PLAYER_DEFAULT && p->id != player->id &&
            p->position.x == player->position.x &&
            p->position.y == player->position.y) {
            eject_player(server, player, p);
            ok = true;
        }
    });
    if (ok)
        notify_graphic(server, "pex %d\n", player->id);
    dprintf(player->client.fd, ok ? "ok\n" : "ko\n");
    return (true);
}
