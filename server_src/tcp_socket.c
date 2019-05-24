/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "tcp_socket.h"

int create_server_tcp_socket(in_port_t port)
{
    struct sockaddr_in addr = {0};
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (fd == -1) {
        perror("socket");
        return (-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ntohl(INADDR_ANY);
    addr.sin_port = port;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    if (bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) == -1 ||
        listen(fd, TCP_MAX_CONNECTION) == -1) {
        close(fd);
        perror("bind/listen");
        return (-1);
    }
    return (fd);
}
