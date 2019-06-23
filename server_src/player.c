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

const position_t DIRECTIONS[] = {
    [NORTH] = {0, 1},
    [EAST] = {1, 0},
    [SOUTH] = {0, -1},
    [WEST] = {-1, 0},
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
    client_reply(player->client.fd, "dead\n");
    player->state = PLAYER_DEAD;
    get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER]--;
    server->clients_limits[player->team_id]++;
    notify_graphic(server, "pdi %d\n", player->id);
    dispatch_event(server, EVT_DEAD, player);
}

void player_move(zappy_server_t *server, player_t *player, int x, int y)
{
    get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER] -= 1;
    player->position.x += x;
    player->position.y += y;
    while (player->position.x < 0)
        player->position.x += server->map->width;
    while (player->position.y < 0)
        player->position.y += server->map->height;
    player->position.x %= server->map->width;
    player->position.y %= server->map->height;
    get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER] += 1;
    notify_graphic(server, "ppo %d %d %d %d\n", player->id, player->position.x,
        player->position.y, player->direction);
}
