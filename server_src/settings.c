/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "zappy.h"

static bool parse_args(zappy_settings_t *settings, char *const args[])
{
    if (args['p'] == NULL || args['x'] == NULL || args['y'] == NULL ||
        args['c'] == NULL || settings->team_names == NULL)
        return (false);
    errno = 0;
    settings->port = htons((in_port_t)strtoul(args['p'], NULL, 10));
    if (args['f'] != NULL)
        settings->freq = (unsigned int)strtoul(args['f'], NULL, 10);
    settings->nb_clients = strtoul(args['c'], NULL, 10);
    settings->width = strtoul(args['x'], NULL, 10);
    settings->height = strtoul(args['y'], NULL, 10);
    if (errno != 0 || settings->port == 0 || settings->freq == 0 ||
        settings->height == 0 || settings->width == 0 ||
        settings->nb_clients == 0)
        return (false);
    return (true);
}

static void get_team_names(zappy_settings_t *settings, int ac, char *const *av,
    int idx)
{
    char **names = NULL;

    for (int i = 0 ; idx + i < ac && av[idx + i][0] != '-' ; ++i) {
        settings->nb_teams++;
        names = realloc(names, sizeof(char *) * (settings->nb_teams + 1));
        if (names == NULL)
            return;
        names[i] = strdup(av[idx + i]);
        if (names[i] == NULL) {
            free(names);
            return;
        }
        names[i + 1] = NULL;
    }
    settings->team_names = names;
}

bool parse_settings(zappy_settings_t *settings, int ac, char *const *av)
{
    int old_optind = 0;
    char *args[] = {
        ['p'] = NULL, ['x'] = NULL, ['y'] = NULL, ['c'] = NULL, ['f'] = NULL
    };

    for (int opt ; (opt = getopt(ac, av, "p:x:y:n:c:f:")) != -1 ;) {
        if (opt == 'n' && settings->team_names == NULL)
            get_team_names(settings, ac,av, old_optind + 1);
        else if (strchr("pxycf", opt) != NULL)
            args[opt] = optarg;
        else
            return (false);
        old_optind = optind;
    }
    return (parse_args(settings, args));
}
