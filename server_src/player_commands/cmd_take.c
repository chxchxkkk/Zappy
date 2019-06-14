/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <string.h>
#include "zappy.h"

static bool on_error(const player_t *player)
{
    dprintf(player->client.fd, "ko\n");
    return (false);
}

bool cmd_take(zappy_server_t *server, player_t *player, char *const *args)
{
    int obj_type = -1;
    unsigned int *objects;

    for (int i = 0 ; i < NB_GAME_OBJECTS ; ++i)
        if (strcmp(OBJ_NAMES[i], args[1]) == 0) {
            obj_type = i;
            break;
        }
    if (obj_type < 0 || obj_type == PLAYER)
        return (on_error(player));
    objects = &get_cell(server->map, player->position.x,
        player->position.y)->objects[obj_type];
    if (*objects == 0)
        return (on_error(player));
    (*objects)--;
    player->inventory[obj_type]++;
    dprintf(player->client.fd, "ok\n");
    notify_graphic(server, "pgt %d %d\n", player->id, obj_type - 1);
    return (true);
}
