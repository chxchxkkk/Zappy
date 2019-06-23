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

static void check_win(const zappy_server_t *server)
{
    const char *winner = NULL;

    for (size_t i = 0 ; i < server->settings.nb_teams ; ++i) {
        size_t n = 0;
        LIST_FOREACH(p, server->player_list, {
            n += (p->state == PLAYER_DEFAULT && p->team_id == (int)i &&
                p->level >= MAX_LEVEL);
        });
        if (n >= 6)
            winner = server->settings.team_names[i];
    }
    if (winner != NULL) {
        notify_graphic(server, "seg %s\n", winner);
        is_server_running(&(bool){false});
    }
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
    check_win(server);
}
