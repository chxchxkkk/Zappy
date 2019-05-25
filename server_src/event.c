/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <malloc.h>
#include <string.h>
#include "event.h"
#include "zappy.h"

void dispatch_event(zappy_server_t *server, enum zappy_event event, ...)
{
    va_list ap;
    va_list aq;

    va_start(ap, event);
    for (size_t i = 0 ; i < server->manager.sizes[event] ; ++i) {
        va_copy(aq, ap);
        server->manager.listeners[event][i](server, &aq);
        va_end(aq);
    }
    va_end(ap);
}

void add_listener(event_manager_t *manager, enum zappy_event event,
    event_listener_t listener)
{
    manager->listeners[event] = realloc(manager->listeners[event],
        sizeof(event_listener_t) * (manager->sizes[event] + 1));
    if (manager->listeners[event] == NULL) {
        manager->sizes[event] = 0;
        return;
    }
    manager->listeners[event][manager->sizes[event]] = listener;
    manager->sizes[event]++;
}

void remove_listener(event_manager_t *manager, enum zappy_event event,
    event_listener_t listener)
{
    for (size_t i = 0 ; i < manager->sizes[event] ; ++i) {
        if (listener == manager->listeners[event][i]) {
            memmove(&manager->listeners[event][i],
                &manager->listeners[event][i + 1],
                sizeof(event_listener_t) * (manager->sizes[event] - i));
            manager->sizes[event]--;
            break;
        }
    }
}

void clear_listeners(event_manager_t *manager, enum zappy_event event)
{
    free(manager->listeners[event]);
    manager->listeners[event] = NULL;
    manager->sizes[event] = 0;
}
