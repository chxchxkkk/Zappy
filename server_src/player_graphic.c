/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "zappy.h"
#include "commands.h"

const struct cmd_entry GRAPHIC_CMDS[] = {
    {"msz", 0, 0, cmd_msz},
    {"bct", 2, 0, cmd_bct},
    {"mct", 0, 0, cmd_mct},
    {"sgt", 0, 0, cmd_sgt},
    {"tna", 0, 0, cmd_tna},
    {"sst", 1, 0, cmd_sst},
    {"ppo", 1, 0, cmd_ppo},
    {"plv", 1, 0, cmd_plv},
    {"pin", 1, 0, cmd_pin},
    {NULL, 0, 0, NULL},
};

static bool parse_command(zappy_server_t *server, player_t *player)
{
    CLEAN(clean_strarr) char **args = str_split(player->commands[0], " \t");
    bool status = false;

    if (args != NULL && args[0] != NULL)
        for (size_t i = 0 ; !status && GRAPHIC_CMDS[i].name != NULL ; ++i)
            if (strcmp(GRAPHIC_CMDS[i].name, args[0]) == 0 &&
                (GRAPHIC_CMDS[i].args == -1 ||
                    (int)strarr_len(args) == GRAPHIC_CMDS[i].args + 1))
                status = true | GRAPHIC_CMDS[i].action(server, player, args);
    free(player->commands[0]);
    memmove(player->commands, &player->commands[1],
        sizeof(*player->commands) * (COMMANDS_BUF - 1));
    player->commands[COMMANDS_BUF - 1] = NULL;
    return (status);
}


void update_player_graphic(zappy_server_t *server, player_t *player)
{
    if (player->commands[0] != NULL && !parse_command(server, player))
        dprintf(player->client.fd, "suc\n");
}
