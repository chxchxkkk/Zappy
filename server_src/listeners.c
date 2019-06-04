/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include "player.h"
#include "event.h"
#include "utils.h"

void on_food_decay(UNUSED zappy_server_t *server, va_list *ap)
{
    player_t *player = va_arg(*ap, player_t *);

    player->inventory[FOOD]--;
}
