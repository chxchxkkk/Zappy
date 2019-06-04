/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <zappy.h>
#include "utils.h"
#include "commands.h"

bool cmd_inventory(UNUSED zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    int idx = 0;
    char buff[BUFSIZ] = "";

    for (size_t i = 1 ; i < NB_GAME_OBJECTS ; ++i)
        idx += snprintf(&buff[idx], (size_t)(BUFSIZ - idx),
            i != NB_GAME_OBJECTS - 1 ? "%s %d, " : "%s %d",
            OBJ_NAMES[i], player->inventory[i]);
    dprintf(player->client.fd, "[ %s ]\n", buff);
    return (true);
}
