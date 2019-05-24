/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <unistd.h>
#include <stdio.h>
#include "zappy.h"
#include "tcp_socket.h"

bool server_init(zappy_server_t *server)
{
    printf("Port: %d\n", ntohs(server->settings.port));
    server->sock = create_server_tcp_socket(server->settings.port);
    server->map = generate_map(server->settings.width, server->settings.height,
        1.0f);
    if (server->sock == -1 || server->map == NULL)
        return (false);
    return (true);
}

int server_run(zappy_server_t *server)
{
    server->running = true;
    while (server->running) {
        sleep(1);
        server->running = false;
    }
    return (0);
}
