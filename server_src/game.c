/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include "zappy.h"
#include "utils.h"

static bool player_is_dead(const player_t *player, UNUSED va_list *ap)
{
    return player->state == PLAYER_DEAD;
}

static bool egg_is_connected(const egg_t *egg, UNUSED va_list *ap)
{
    return egg->connected;
}

void update_game(zappy_server_t *server)
{
    LIST_FOREACH(player, server->player_list, {
        update_player(server, player);
    });
    LIST_FOREACH(egg, server->egg_list, {
        update_egg(server, egg);
    });
    LIST_DELETE_MATCHING(&server->player_list, player_is_dead, free_player);
    LIST_DELETE_MATCHING(&server->egg_list, egg_is_connected, free);
}
