/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include "zappy.h"
#include "utils.h"

void print_cell_content(const cell_t *cell, int fd, int x, int y)
{
    dprintf(fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        cell->objects[FOOD],
        cell->objects[LINEMATE],
        cell->objects[DERAUMERE],
        cell->objects[SIBUR],
        cell->objects[MENDIANE],
        cell->objects[PHIRAS],
        cell->objects[THYSTAME]);
}

bool cmd_bct(zappy_server_t *server, player_t *player, char *const *args)
{
    unsigned int x = (unsigned int)strtoul(args[1], NULL, 10);
    unsigned int y = (unsigned int)strtoul(args[2], NULL, 10);
    cell_t *cell;

    if (x > server->map->width || y > server->map->height) {
        dprintf(player->client.fd, "sbp\n");
        return (false);
    }
    cell = get_cell(server->map, x, y);
    print_cell_content(cell, player->client.fd, x, y);
    return (true);
}
