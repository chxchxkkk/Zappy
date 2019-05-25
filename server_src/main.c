/*
** EPITECH PROJECT, 2017
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"
#include "zappy.h"

static void usage(void)
{
    puts("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ..."
         " -c clientsNb -f freq\n"
         "\tport\tis the port number\n"
         "\twidth\tis the width of the world\n"
         "\theight\tis the height of the world\n"
         "\tnameX\tis the name of the team X \n"
         "\tclientsNb\tis the number of authorized clients per team \n"
         "\tfreq\tis the reciprocal of time unit for execution of actions");
}

static void clean_server(zappy_server_t *server)
{
    LIST_FREE(&server->player_list, free_player);
    if (server->sock > 0) {
        shutdown(server->sock, SHUT_RDWR);
        close(server->sock);
    }
    for (size_t i = 0 ; i < server->settings.nb_teams ; ++i)
        free(server->settings.team_names[i]);
    if (server->map != NULL)
        free_map(server->map);
    free(server->settings.team_names);
}

int main(int ac, char *const *av)
{
    CLEAN(clean_server) zappy_server_t server = {
        .settings = {0, .freq = 100},
        .maxfd = 0, .fdset = {}, .sock = 0, .player_list = NULL, .map = NULL
    };

    srand((unsigned int)time(NULL));
    if (!parse_settings(&server.settings, ac, av)) {
        usage();
        return (84);
    }
    if (!server_init(&server))
        return (84);
    return (server_run(&server));
}
