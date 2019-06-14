/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"

void notify_graphic(const zappy_server_t *server, const char *fmt, ...)
{
    va_list ap;
    va_list cpy;

    va_start(ap, fmt);
    LIST_FOREACH(player, server->player_list, {
        va_copy(cpy, ap);
        if (player->state == PLAYER_GRAPHIC)
            vdprintf(player->client.fd, fmt, cpy);
        va_end(cpy);
    });
    va_end(ap);
}

void notify_graphic_cmd(zappy_server_t *server, action_func_t cmd,
    char *const *args)
{
    LIST_FOREACH(player, server->player_list, {
        if (player->state == PLAYER_GRAPHIC)
            cmd(server, player, args);
    });
}
