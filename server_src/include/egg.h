/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "player.h"
#include "list.h"

#define EGG_HATCH_TIME  600

typedef struct egg {
    list_t;
    position_t position;
    unsigned int id;
    int team_id;
    float hatch_time;
    bool hatched;
    bool connected;
} egg_t;

egg_t *lay_egg(zappy_server_t *server, const player_t *player);
void update_egg(zappy_server_t *server, egg_t *egg);
