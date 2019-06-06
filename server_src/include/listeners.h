/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "event.h"
#include "utils.h"

void on_food_decay(zappy_server_t *server, va_list *ap);
void on_connect(UNUSED zappy_server_t *server, va_list *ap);
void on_player_spawn(zappy_server_t *server, va_list *ap);
void on_disconnect(zappy_server_t *server, va_list *ap);
