/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <zappy.h>
#include "player.h"
#include "event.h"
#include "utils.h"

void on_food_decay(UNUSED zappy_server_t *server, va_list *ap)
{
    player_t *player = va_arg(*ap, player_t *);

    player->inventory[FOOD]--;
}

void on_connect(UNUSED zappy_server_t *server, va_list *ap)
{
    player_t *player = va_arg(*ap, player_t *);

    dprintf(player->client.fd, "WELCOME\n");
}

void on_player_spawn(zappy_server_t *server, va_list *ap)
{
    player_t *player = va_arg(*ap, player_t *);

    server->clients_limits[player->team_id]--;
    dprintf(player->client.fd, "%ld\n",
        server->clients_limits[player->team_id]);
    dprintf(player->client.fd, "%ld %ld\n", server->map->width,
        server->map->height);
}

void on_disconnect(zappy_server_t *server, va_list *ap)
{
    player_t *player = va_arg(*ap, player_t *);

    if (player->state == PLAYER_DEAD || player->state == PLAYER_DEFAULT) {
        get_cell(server->map, player->position.x,
            player->position.y)->objects[PLAYER]--;
        server->clients_limits[player->team_id]++;
    }
}
