/*
** EPITECH PROJECT, 2017
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
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

static void clean_settings(zappy_settings_t *settings)
{
    for (size_t i = 0 ; i < settings->nb_teams ; ++i)
        free(settings->team_names[i]);
    free(settings->team_names);
}

int main(int ac, char *const *av)
{
    CLEAN(clean_settings) zappy_settings_t settings = {0, .freq = 100};

    if (!parse_settings(&settings, ac, av)) {
        usage();
        return (84);
    }
    printf("port: %d\n", ntohs(settings.port));
    printf("width: %ld\n", settings.width);
    printf("height: %ld\n", settings.height);
    printf("clientsNb: %ld\n", settings.nb_clients);
    printf("freq: %d\n", settings.freq);
    printf("nb teams: %ld\n", settings.nb_teams);
    printf("team names:\n");
    for (size_t i = 0 ; i < settings.nb_teams ; ++i)
        printf("\t%s\n", settings.team_names[i]);
    return (0);
}
