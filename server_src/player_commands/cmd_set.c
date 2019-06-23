/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <string.h>
#include "zappy.h"
#include "commands.h"

static bool on_error(const player_t *player)
{
    client_reply(player->client.fd, "ko\n");
    return (false);
}

static void notify_graphic_take(zappy_server_t *server, const player_t *player,
    int obj_type)
{
    char player_id[16] = "";
    char x[16] = "";
    char y[16] = "";

    snprintf(player_id, 16, "%d", player->id);
    snprintf(x, 16, "%d", player->position.x);
    snprintf(y, 16, "%d", player->position.y);
    notify_graphic(server, "pdr %d %d\n", player->id, obj_type - 1);
    notify_graphic_cmd(server, cmd_pin, (char *[]){"pin", player_id});
    notify_graphic_cmd(server, cmd_bct, (char *[]){"bct", x, y});
}

bool cmd_set(zappy_server_t *server, player_t *player, char *const *args)
{
    int obj_type = -1;
    int *objects;

    for (int i = 0 ; i < NB_GAME_OBJECTS ; ++i)
        if (strcmp(OBJ_NAMES[i], args[1]) == 0) {
            obj_type = i;
            break;
        }
    if (obj_type < 0 || obj_type == PLAYER)
        return (on_error(player));
    objects = &player->inventory[obj_type];
    if (*objects <= 0)
        return (on_error(player));
    (*objects)--;
    get_cell(server->map, player->position.x,
        player->position.y)->objects[obj_type]++;
    client_reply(player->client.fd, "ok\n");
    notify_graphic_take(server, player, obj_type);
    return (true);
}
