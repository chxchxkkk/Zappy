/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <unistd.h>
#include <stdio.h>
#include "utils.h"
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
    server->maxfd = server->sock;
    return (true);
}

void accept_client(zappy_server_t *server)
{
    struct sockaddr_in addr = {0};
    socklen_t len = sizeof(addr);
    int fd = accept(server->socket->fd, (struct sockaddr *)&addr, &len);
    client_t *client = NULL;

    if (fd == -1) {
        perror("accept:");
        return;
    }
    if (fd >= FD_SETSIZE || (client = LIST_PUSH(&server->clients,
        create_client(fd, &addr))) == NULL) {
        close(fd);
        fprintf(stderr, "error when accepting client." CRLF);
        return;
    }
    reply_client(client, FTP_CONNECTION, "Connected.");
    server->maxfd = fd > server->maxfd ? fd : server->maxfd;

}

void update_game(zappy_server_t *server)
{

}

int server_run(zappy_server_t *server)
{
    server->running = true;
    map_info(server->map);
    while (server->running) {
       FD_ZERO(&server->fdset);
       FD_SET(server->sock, &server->fdset);
       LIST_FOREACH(player, server->player_list, {
            FD_SET(player->client.fd, &server->fdset);
       });
       if (select(server->maxfd + 1, &server->fdset, NULL, NULL, NULL) == -1) {
           perror("select");
           return (84);
       }
       if (FD_ISSET(server->sock, &server->fdset))
           accept_client(server);
       else
           update_game(server);
    }
    return (0);
}
