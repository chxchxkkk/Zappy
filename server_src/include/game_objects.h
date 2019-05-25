/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#define NB_GAME_OBJECTS  8

enum game_objects {
    PLAYER,
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
};

/**
* @property resource: type of the resource
* @property max: maximal number generated per cell
* @property rarity: chance between 0.0 and 1.0 to spawn when generating the map
* 0.0: never spawns
* 1.0: spawns [max] number of this resource on every cell
*/
struct resource_rarity {
    enum game_objects resource;
    int max;
    float rarity;
};

extern const struct resource_rarity RARITIES[NB_GAME_OBJECTS];
extern const char *OBJ_NAMES[NB_GAME_OBJECTS];
