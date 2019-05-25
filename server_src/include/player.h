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
#define MAX_LEVEL       8

enum direction {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
};

typedef struct position {
    unsigned int x;
    unsigned int y;
} position_t;

enum player_state {
    PLAYER_UNINITIALIZED,
    PLAYER_DEFAULT,
    PLAYER_GRAPHIC,
};

typedef struct player {
    list_t;
    client_t client;
    position_t position;
    char *commands[COMMANDS_BUF];
    int inventory[NB_GAME_OBJECTS];
    unsigned int level;
    int team_id;
    enum direction direction;
    enum player_state state;
} player_t;

void free_player(player_t *player);

extern const int ELEVATION_CHART[MAX_LEVEL][NB_GAME_OBJECTS];
