/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <string.h>
#include "zappy.h"
#include "utils.h"

static const int ELEVATION_CHART[MAX_LEVEL][NB_GAME_OBJECTS] = {
    [0] = {0},
    /* player food linemate deraumere sibur mendiane phiras thystame */
    [1] = {1, -1, 1, 0, 0, 0, 0, 0},
    [2] = {2, -1, 1, 1, 1, 0, 0, 0},
    [3] = {2, -1, 2, 0, 1, 0, 2, 0},
    [4] = {4, -1, 1, 1, 2, 0, 1, 0},
    [5] = {4, -1, 1, 2, 1, 3, 0, 0},
    [6] = {6, -1, 1, 2, 3, 0, 1, 0},
    [7] = {6, -1, 2, 2, 2, 2, 2, 1},
};

static bool check_requirements(const cell_t *cell, const player_t *player)
{
    for (size_t i = 0 ; i < ARRAY_LEN(ELEVATION_CHART) ; ++i)
        if (ELEVATION_CHART[player->level][i] >= 0 &&
            (unsigned int)ELEVATION_CHART[player->level][i] != cell->objects[i])
            return (false);
    return (true);
}

bool do_incantation(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    unsigned int level = player->level + 1;

    notify_graphic(server, "pie %d %d %d\n", player->position.x,
        player->position.y, player->level);
    LIST_FOREACH(p, server->player_list, {
        if (p->state == PLAYER_DEFAULT && p->position.x == player->position.x &&
            p->position.y == player->position.y) {
            p->level = level;
            dprintf(p->client.fd, "Current level: %d\n", level);
            notify_graphic(server, "plv %d %d\n", p->id, player->level);
        }
    });
    player->action.fptr = NULL;
    return (true);
}

bool wait_incantation(UNUSED zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    player->action.fptr = NULL;
    return (true);
}

static void begin_incantation(const zappy_server_t *server, player_t *player)
{
    clean_strarr(&player->action.args);
    player->action.cooldown = 300.0f / server->settings.freq;
    player->action.args = NULL;
    player->action.fptr = wait_incantation;
    dprintf(player->client.fd, "Elevation underway\n");
}

bool cmd_incantation(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    size_t nb_players = get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER];
    char msg[BUFSIZ] = "";
    size_t i = 0;

    if (player->level >= MAX_LEVEL || !check_requirements(
        get_cell(server->map, player->position.x, player->position.y), player))
        return (dprintf(player->client.fd, "ko\n"), false);
    LIST_FOREACH(p, server->player_list, {
        if (p->state == PLAYER_DEFAULT && p->position.x == player->position.x &&
            p->position.y == player->position.y) {
            begin_incantation(server, p);
            i += snprintf(&msg[i],
                BUFSIZ - i, i + 1 == nb_players ? "%d" : "%d ", p->id);
        }
    });
    notify_graphic(server, "pic %d %d %d %s\n", player->position.x,
        player->position.y, player->level, msg);
    player->action.fptr = do_incantation;
    return (true);
}

