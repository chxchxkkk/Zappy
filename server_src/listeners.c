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
#include "commands.h"

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
    notify_graphic(server, "pnw %d %d %d %d %d %s\n", player->id,
        player->position.x, player->position.y, player->direction,
        player->level + 1, server->settings.team_names[player->team_id]);
    refill_food(server);
}

void on_disconnect(zappy_server_t *server, va_list *ap)
{
    player_t *player = va_arg(*ap, player_t *);

    if (player->state == PLAYER_DEFAULT)
        kill_player(server, player);
    else
        LIST_DELETE(&server->player_list, player, free_player);
}

void on_graphic_connect(zappy_server_t *server, va_list *ap)
{
    player_t *player = va_arg(*ap, player_t *);

    cmd_msz(server, player, NULL);
    cmd_sgt(server, player, NULL);
    cmd_mct(server, player, NULL);
    cmd_tna(server, player, NULL);
}
