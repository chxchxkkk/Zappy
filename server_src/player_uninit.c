/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <string.h>
#include "zappy.h"

/* TODO attribute player ID */
static void init_player(zappy_server_t *server, player_t *player, int team_id)
{
    player->state = PLAYER_DEFAULT;
    player->inventory[FOOD] = 10;
    player->food_cooldown = (float)FOOD_DECAY / server->settings.freq;
    player->position.x = (int)(rand() % server->map->width);
    player->position.y = (int)(rand() % server->map->height);
    player->direction = rand() % 4 + 1;
    player->team_id = team_id;
    player->id = 0;
    get_cell(server->map, player->position.x,
        player->position.y)->objects[PLAYER] += 1;
    dispatch_event(server, EVT_SPAWN, player);
}

static void init_graphic(zappy_server_t *server, player_t *player)
{
    player->state = PLAYER_GRAPHIC;
    dispatch_event(server, EVT_GRAPHIC_CONNECT, player);
}

static void register_command(zappy_server_t *server, player_t *player)
{
    if (strcmp(player->commands[0], "GRAPHIC") == 0)
        init_graphic(server, player);
    else
        for (size_t i = 0 ; i < server->settings.nb_teams ; ++i)
            if (!strcmp(server->settings.team_names[i], player->commands[0]))
                init_player(server, player, (int)i);
    dprintf(player->client.fd,
        player->state == PLAYER_UNINITIALIZED ? "ko\n" : "ok\n");
    free(player->commands[0]);
    memmove(player->commands, &player->commands[1],
        sizeof(*player->commands) * (COMMANDS_BUF - 1));
    player->commands[COMMANDS_BUF - 1] = NULL;
}

void update_player_uninit(zappy_server_t *server, player_t *player)
{
    if (player->commands[0] != NULL)
        register_command(server, player);
}
