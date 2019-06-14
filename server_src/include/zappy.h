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
#include "event.h"

#define SERVER_TICKRATE 120

typedef struct zappy_settings {
    char **team_names;
    size_t nb_teams;
    size_t clients_limit;
    size_t width;
    size_t height;
    unsigned int freq;
    in_port_t port;
} zappy_settings_t;

bool parse_settings(zappy_settings_t *settings, int ac, char *const *av);

typedef struct zappy_server {
    zappy_settings_t settings;
    event_manager_t manager;
    fd_set fdset;
    player_t *player_list;
    map_t *map;
    size_t *clients_limits;
    int sock;
    int maxfd;
    float dt;
} zappy_server_t;

bool server_init(zappy_server_t *server);
int server_run(zappy_server_t *server);
bool is_server_running(const bool *set);

bool process_player_input(zappy_server_t *server, player_t *player);

void update_game(zappy_server_t *server);
void refill_food(zappy_server_t *server);

void catch_sigint(int sig);

void notify_graphic(const zappy_server_t *server, const char *fmt, ...)
    __attribute__((format (printf, 2, 3)));
