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
#include "event.h"

#define FOOD_DECAY      126
#define COMMANDS_BUF    10
#define MAX_LEVEL       8

enum direction {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
};

typedef struct position {
    int x;
    int y;
} position_t;

enum player_state {
    PLAYER_UNINITIALIZED,
    PLAYER_DEFAULT,
    PLAYER_GRAPHIC,
    PLAYER_DEAD,
};

typedef struct player player_t;

typedef bool (*action_func_t)(zappy_server_t *server, player_t *player,
    char *const *args);

typedef struct action {
    action_func_t fptr;
    char **args;
    float cooldown;
} action_t;

typedef struct player {
    list_t;
    client_t client;
    position_t position;
    action_t action;
    char *commands[COMMANDS_BUF];
    int inventory[NB_GAME_OBJECTS];
    unsigned int level;
    float food_cooldown;
    int id;
    int team_id;
    enum direction direction;
    enum player_state state;
} player_t;

void free_player(player_t *player);
player_t *create_player(int fd, const struct sockaddr_in *sa);
void kill_player(zappy_server_t *server, player_t *player);
void update_player(zappy_server_t *server, player_t *player);
void update_player_default(zappy_server_t *server, player_t *player);
void update_player_graphic(zappy_server_t *server, player_t *player);
void update_player_uninit(zappy_server_t *server, player_t *player);

bool do_incantation(zappy_server_t *server, player_t *player,
    char *const *args);
bool wait_incantation(zappy_server_t *server, player_t *player,
    char *const *args);
