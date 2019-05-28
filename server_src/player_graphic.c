/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include "utils.h"
#include "zappy.h"
#include "commands.h"

const struct cmd_entry GRAPHIC_CMDS[] = {
    {NULL, 0, 0, NULL},
};

static void register_command(player_t *player)
{
    free(player->commands[0]);
    memmove(player->commands, &player->commands[1],
        sizeof(*player->commands) * (COMMANDS_BUF - 1));
    player->commands[COMMANDS_BUF - 1] = NULL;
}

void update_player_graphic(UNUSED zappy_server_t *server, player_t *player)
{
    if (player->commands[0] != NULL)
        register_command(player);
}
