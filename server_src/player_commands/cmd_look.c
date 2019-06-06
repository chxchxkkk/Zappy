/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <zappy.h>
#include <string.h>
#include "utils.h"
#include "commands.h"

char *get_cell_content(const cell_t *cell)
{
    int idx = 0;
    char buff[BUFSIZ] = "";

    for (size_t i = 0 ; i < NB_GAME_OBJECTS ; ++i)
        for (size_t j = 0 ; j < cell->objects[i] ; ++j)
            idx += snprintf(&buff[idx], (size_t)(BUFSIZ - idx), " %s",
                OBJ_NAMES[i]);
    return strdup(buff);
}

bool cmd_look(zappy_server_t *server, player_t *player,
    UNUSED char *const *args)
{
    CLEAN(clean_ptr) cell_t **cells = get_vision_cells(server->map, player);
    CLEAN(clean_ptr) char *buff = NULL;

    for (size_t i = 0 ; cells != NULL && cells[i] != NULL ; ++i) {
        buff = va_strcat(true, 2, buff, va_strcat(true, 2,
            get_cell_content(cells[i]),
            cells[i + 1] != NULL ? strdup(",") : strdup("")));
    }
    if (buff == NULL) {
        dprintf(player->client.fd, "[]\n");
        return (false);
    }
    dprintf(player->client.fd, "[%s ]\n", buff);
    return (true);
}
