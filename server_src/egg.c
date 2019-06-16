/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <math.h>
#include "zappy.h"

egg_t *lay_egg(zappy_server_t *server, const player_t *player)
{
    static unsigned int egg_id_generator = 0;
    egg_t *egg = LIST_CREATE(egg_t);

    if (egg == NULL)
        return (NULL);
    egg->id = egg_id_generator++;
    egg->team_id = player->team_id;
    egg->position = player->position;
    egg->hatch_time = (float)EGG_HATCH_TIME / server->settings.freq;
    egg->hatched = false;
    egg->connected = false;
    notify_graphic(server, "pfk %d\n", player->id);
    notify_graphic(server, "enw %d %d %d %d\n", egg->id, player->id,
        egg->position.x, egg->position.y);
    return LIST_PUSH(&server->egg_list, egg);
}

void update_egg(zappy_server_t *server, egg_t *egg)
{
    if (egg->hatched)
        return;
    egg->hatch_time -= server->dt;
    if (egg->hatch_time <= 0.0f) {
        server->clients_limits[egg->team_id]++;
        egg->hatched = true;
        notify_graphic(server, "eht %d\n", egg->id);
    }
}
