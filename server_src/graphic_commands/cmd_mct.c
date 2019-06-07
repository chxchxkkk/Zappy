/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include "zappy.h"
#include "utils.h"

bool cmd_mct(zappy_server_t *server, player_t *player, UNUSED char *const *args)
{
    for (int x = 0 ; x < (int)server->map->width ; ++x)
        for (int y = 0 ; y < (int)server->map->height ; ++y)
            print_cell_content(get_cell(server->map, x, y), player->client.fd,
                x, y);
    return (true);
}
