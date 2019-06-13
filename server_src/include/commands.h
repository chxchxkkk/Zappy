/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <stdbool.h>
#include "player.h"

struct cmd_entry {
    const char *name;
    int args;
    unsigned int time;
    action_func_t action;
};

/*
* Player commands
*/
bool cmd_forward(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_right(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_left(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_inventory(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_look(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_take(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_set(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_broadcast(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_connect_nbr(zappy_server_t *server, player_t *player,
    char *const *args);

/*
* Graphic commands
*/
bool cmd_msz(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_bct(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_mct(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_sgt(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_tna(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_sst(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_ppo(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_plv(zappy_server_t *server, player_t *player, char *const *args);
bool cmd_pin(zappy_server_t *server, player_t *player, char *const *args);

extern const struct cmd_entry PLAYER_CMDS[];
extern const struct cmd_entry GRAPHIC_CMDS[];
