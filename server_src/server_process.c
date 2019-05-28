/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include "get_next_line.h"
#include "utils.h"
#include "zappy.h"

bool process_player_input(UNUSED zappy_server_t *server,
    player_t *player)
{
    CLEAN(clean_ptr) char *line = get_next_line(player->client.fd);

    if (line == NULL)
        return (false);
    for (size_t i = 0 ; i < COMMANDS_BUF ; ++i) {
        if (player->commands[i] == NULL) {
            player->commands[i] = strdup(line);
            break;
        }
    }
    return (true);
}
