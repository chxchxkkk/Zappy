/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "client.h"

void free_client(client_t *client)
{
    if (client->fd <= 0)
        return;
    shutdown(client->fd, SHUT_RDWR);
    close(client->fd);
}

void client_reply(int fd, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    va_client_reply(fd, fmt, &ap);
    va_end(ap);
}

void va_client_reply(int fd, const char *fmt, va_list *ap)
{
    int len;
    char *msg = NULL;

    if ((len = vasprintf(&msg, fmt, *ap)) != -1)
        send(fd, msg, (size_t)len, MSG_NOSIGNAL);
    free(msg);
}
