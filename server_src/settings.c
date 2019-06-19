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
#include "utils.h"

static bool is_unique(char *const *array)
{
    for (size_t i = 0 ; array[i] != NULL ; ++i)
        for (size_t j = 0 ; array[j] != NULL ; ++j)
            if (i != j && strcmp(array[i], array[j]) == 0)
                return (false);
    return (true);
}

static bool parse_args(zappy_settings_t *settings, char *const args[])
{
    errno = 0;
    if (args['p'] != NULL)
        settings->port = htons((in_port_t)strtoul(args['p'], NULL, 10));
    if (args['f'] != NULL)
        settings->freq = (unsigned int)strtoul(args['f'], NULL, 10);
    if (args['c'] != NULL)
        settings->clients_limit = strtoul(args['c'], NULL, 10);
    if (args['x'] != NULL)
        settings->width = strtoul(args['x'], NULL, 10);
    if (args['y'] != NULL)
        settings->height = strtoul(args['y'], NULL, 10);
    if (settings->team_names == NULL)
        settings->nb_teams = strarr_len(
            settings->team_names = str_split("Team1 Team2 Team3 Team4", " "));
    if (errno != 0 || settings->port == 0 || settings->freq == 0 ||
        settings->height == 0 || settings->width == 0 ||
        settings->team_names == NULL || settings->clients_limit == 0 ||
        !is_unique(settings->team_names))
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
    int old_optind = 1;
    char *args[] = {
        ['p'] = NULL, ['x'] = NULL, ['y'] = NULL, ['c'] = NULL, ['f'] = NULL
    };

    for (int opt ; (opt = getopt(ac, av, "p:x:y:n:c:f:")) != -1 ;) {
        if (opt == 'n' && settings->team_names == NULL)
            get_team_names(settings, ac, av, old_optind + 1);
        else if (strchr("pxycf", opt) != NULL)
            args[opt] = optarg;
        else
            return (false);
        old_optind = optind;
    }
    return (parse_args(settings, args));
}
