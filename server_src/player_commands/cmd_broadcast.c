/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <math.h>
#include "zappy.h"
#include "utils.h"

static const position_t MAP_DIRECTIONS[] = {
    {0, 0},
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};

static int get_distance(const position_t *a, const position_t *b)
{
    return (abs(b->x - a->x) + abs(b->y - a->y));
}

static position_t get_shortest_position(const map_t *map,
    const position_t *from, const position_t *to)
{
    int shortest = INT32_MAX;
    size_t shortest_idx = 0;
    int distance;

    for (size_t i = 0 ; i < ARRAY_LEN(MAP_DIRECTIONS) ; ++i) {
        distance = get_distance(from,
            &(position_t){
                to->x + MAP_DIRECTIONS[i].x * (int)map->width,
                to->y + MAP_DIRECTIONS[i].y * (int)map->height
            });
        if (distance < shortest) {
            shortest = distance;
            shortest_idx = i;
        }
    }
    return ((position_t){
        to->x + MAP_DIRECTIONS[shortest_idx].x * (int)map->width,
        to->y + MAP_DIRECTIONS[shortest_idx].y * (int)map->height
    });
}

static int get_sound_direction(const map_t *map, const position_t *from,
    const position_t *to, enum direction direction)
{
    position_t actual_to = get_shortest_position(map, from, to);
    double angle = (atan2(actual_to.y - from->y, actual_to.x - from->x) +
        M_PI_2) * 180.0 / M_PI;
    int final_direction;

    angle -= (360.0 / 8.0) / 2.0;
    if (from->x == to->x && from->y == to->y)
        return (0);
    while (angle < 0.0)
        angle += 360.0;
    final_direction = (int)ceil(angle / (360.0 / 8.0));
    return ((final_direction + (direction - 1) * 2) % 8) + 1;
}

bool cmd_broadcast(zappy_server_t *server, player_t *player, char *const *args)
{
    CLEAN(clean_ptr) char *msg = str_join(" ", &args[1]);

    if (msg == NULL || strarr_len(args) <= 1) {
        dprintf(player->client.fd, "ko\n");
        return (false);
    }
    LIST_FOREACH(p, server->player_list, {
        if (p->state == PLAYER_DEFAULT && p->id != player->id)
            dprintf(p->client.fd, "message %d, %s\n",
                get_sound_direction(server->map, &player->position,
                    &p->position, p->direction), msg);
    });
    dprintf(player->client.fd, "ok\n");
    return (true);
}
