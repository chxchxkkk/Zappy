/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <stdarg.h>

enum zappy_event {
    EVT_CONNECT,
    EVT_DISCONNECT,
    EVT_SPAWN,
    EVT_DEAD,
    EVT_FORK,
    EVT_ELEVATION,
    EVT_BROADCAST,
    EVT_FOOD_DECAY,
    EVT_GRAPHIC_CONNECT,
    /* always last */
    EVT_SIZE,
};

typedef struct zappy_server zappy_server_t;

typedef void (*event_listener_t)(zappy_server_t *server, va_list *);

typedef struct event_manager {
    event_listener_t *listeners[EVT_SIZE];
    size_t sizes[EVT_SIZE];
} event_manager_t;

void dispatch_event(zappy_server_t *server, enum zappy_event event, ...);
void add_listener(event_manager_t *manager, enum zappy_event event,
    event_listener_t listener);
void remove_listener(event_manager_t *manager, enum zappy_event event,
    event_listener_t listener);
void clear_listeners(event_manager_t *manager, enum zappy_event event);
