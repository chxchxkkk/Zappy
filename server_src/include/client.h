/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <netinet/in.h>
#include <stdarg.h>

#define CLIENT_BUF  256

typedef struct client {
    struct sockaddr_in sa;
    char buffer[CLIENT_BUF];
    char *read_ptr;
    char *write_ptr;
    int fd;
} client_t;

void free_client(client_t *client);
void client_reply(int fd, const char *fmt, ...);
void va_client_reply(int fd, const char *fmt, va_list *ap);

