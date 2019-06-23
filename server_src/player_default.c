/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "commands.h"
#include "zappy.h"

const struct cmd_entry PLAYER_CMDS[] = {
    {"Forward", 0, 7, cmd_forward},
    {"Right", 0, 7, cmd_right},
    {"Left", 0, 7, cmd_left},
    {"Inventory", 0, 1, cmd_inventory},
    {"Look", 0, 7, cmd_look},
    {"Take", 1, 7, cmd_take},
    {"Set", 1, 7, cmd_set},
    {"Fork", 0, 42, cmd_fork},
    {"Eject", 0, 7, cmd_eject},
    {"Connect_nbr", 0, 0, cmd_connect_nbr},
    {"Broadcast", -1, 7, cmd_broadcast},
    {"Incantation", 0, 0, cmd_incantation},
    {NULL, 0, 0, NULL},
};

static bool register_command(zappy_server_t *server, player_t *player,
    size_t cmd_idx, char **args)
{
    clean_strarr(&player->action.args);
    player->action.fptr = PLAYER_CMDS[cmd_idx].action;
    player->action.args = args;
    player->action.cooldown = (float)PLAYER_CMDS[cmd_idx].time
        / server->settings.freq;
    return (true);
}

static bool parse_command(zappy_server_t *server, player_t *player)
{
    char **args = str_split(player->commands[0], " \t");
    bool status = false;

    if (args != NULL && args[0] != NULL)
        for (size_t i = 0 ; !status && PLAYER_CMDS[i].name != NULL ; ++i)
            if (strcmp(PLAYER_CMDS[i].name, args[0]) == 0 &&
                (PLAYER_CMDS[i].args == -1 ||
                    (int)strarr_len(args) == PLAYER_CMDS[i].args + 1))
                status = register_command(server, player, i, args);
    free(player->commands[0]);
    memmove(player->commands, &player->commands[1],
        sizeof(*player->commands) * (COMMANDS_BUF - 1));
    player->commands[COMMANDS_BUF - 1] = NULL;
    if (status == false)
        clean_strarr(&args);
    return (status);
}

static void bad_command(const player_t *player)
{
    client_reply(player->client.fd, "ko\n");
}

void update_player_default(zappy_server_t *server, player_t *player)
{
    player->action.cooldown -= server->dt;
    player->food_cooldown -= server->dt;
    if (player->food_cooldown <= 0.0f) {
        dispatch_event(server, EVT_FOOD_DECAY, player);
        player->food_cooldown += (float)FOOD_DECAY / server->settings.freq;
    }
    if (player->inventory[FOOD] < 0) {
        kill_player(server, player);
        return;
    }
    if (player->action.cooldown <= 0.0f && player->action.fptr != NULL) {
        player->action.fptr(server, player, player->action.args);
        if (player->action.fptr != do_incantation &&
            player->action.fptr != wait_incantation)
            player->action.fptr = NULL;
    }
    if (player->action.fptr == NULL && player->commands[0] != NULL &&
        !parse_command(server, player))
        bad_command(player);
}
