/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <unistd.h>
#include <stdio.h>
#include "zappy.h"
#include "utils.h"
#include "player.h"

static void (*const UPDATE_CMDS[])(zappy_server_t *, player_t *) = {
    [PLAYER_UNINITIALIZED] = update_player_uninit,
    [PLAYER_DEFAULT] = update_player_default,
    [PLAYER_GRAPHIC] = update_player_graphic,
    [PLAYER_DEAD] = NULL,
};

player_t *create_player(int fd, const struct sockaddr_in *sa)
{
    player_t player = {
        .client = {
            .fd = fd, .sa = *sa, .buffer = {0},
            .read_ptr = player.client.buffer,
            .write_ptr = player.client.buffer
        },
        .next = NULL, .prev = NULL,
        .state = PLAYER_UNINITIALIZED,
        .level = 1, .id = -1, .team_id = -1, .inventory = {0},
        .commands = {NULL}, .position = {0}, .direction = 0,
    };

    return (memdup(&player, sizeof(player)));
}

void free_player(player_t *player)
{
    free_client(&player->client);
    for (size_t i = 0 ; i < ARRAY_LEN(player->commands) ; ++i)
        free(player->commands[i]);
    clean_strarr(&player->action.args);
    free(player);
}

void update_player(zappy_server_t *server, player_t *player)
{
    if (UPDATE_CMDS[player->state] != NULL)
        UPDATE_CMDS[player->state](server, player);
}

void kill_player(zappy_server_t *server, player_t *player)
{
    dprintf(player->client.fd, "dead\n");
    player->state = PLAYER_DEAD;
    get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER]--;
    server->clients_limits[player->team_id]++;
    notify_graphic(server, "pdi %d\n", player->id);
    dispatch_event(server, EVT_DEAD, player);
}
