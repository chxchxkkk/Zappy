/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <netinet/in.h>
#include <stdbool.h>

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

