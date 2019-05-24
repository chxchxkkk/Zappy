/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "game_objects.h"
#include "client.h"
#include "list.h"

#define COMMANDS_BUF    10

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
};

typedef struct player {
    list_t;
    client_t client;
    char *commands[COMMANDS_BUF];
    int inventory[NB_GAME_OBJECTS];
    int team_id;
    enum direction direction;
} player_t;

void free_player(player_t *player);
