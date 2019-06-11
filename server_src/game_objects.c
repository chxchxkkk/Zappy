/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include "game_objects.h"

const struct resource_rarity RARITIES[NB_GAME_OBJECTS] = {
    {PLAYER, 0, 0.0},
    {FOOD, 4, 0.1},
    {LINEMATE, 3, 0.25},
    {DERAUMERE, 3, 0.2},
    {SIBUR, 2, 0.35},
    {MENDIANE, 2, 0.2},
    {PHIRAS, 3, 0.15},
    {THYSTAME, 1, 0.05},
};

const char *OBJ_NAMES[NB_GAME_OBJECTS] = {
    [PLAYER] = "player",
    [FOOD] = "food",
    [LINEMATE] = "linemate",
    [DERAUMERE] = "deraumere",
    [SIBUR] = "sibur",
    [MENDIANE] = "mendiane",
    [PHIRAS] = "phiras",
    [THYSTAME] = "thystame",
};
