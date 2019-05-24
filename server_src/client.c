/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <unistd.h>
#include "client.h"

void free_client(client_t *client)
{
    if (client->fd <= 0)
        return;
    shutdown(client->fd, SHUT_RDWR);
    close(client->fd);
}
