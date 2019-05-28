/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include "utils.h"

bool is_server_running(const bool *set)
{
    static bool running = true;

    if (set != NULL)
        running = *set;
    return running;
}

void catch_sigint(UNUSED int sig)
{
    is_server_running(&(bool){false});
}
