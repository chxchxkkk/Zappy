/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <netinet/in.h>
#include <stdbool.h>
#include "player.h"
#include "map.h"

typedef struct zappy_settings {
    char **team_names;
    size_t nb_teams;
    size_t nb_clients;
    size_t width;
    size_t height;
    unsigned int freq;
    in_port_t port;
} zappy_settings_t;

bool parse_settings(zappy_settings_t *settings, int ac, char *const *av);

typedef struct zappy_server {
    zappy_settings_t settings;
    fd_set fdset;
    player_t *player_list;
    map_t *map;
    int sock;
    int maxfd;
    bool running;
} zappy_server_t;

bool server_init(zappy_server_t *server);
int server_run(zappy_server_t *server);
