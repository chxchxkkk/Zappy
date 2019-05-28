/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include "utils.h"
#include "zappy.h"
#include "tcp_socket.h"

static void accept_client(zappy_server_t *server)
{
    struct sockaddr_in addr = {0};
    int fd = accept(server->sock, (struct sockaddr *)&addr,
        &(socklen_t){sizeof(addr)});
    player_t *player;

    if (fd == -1) {
        perror("accept");
        return;
    }
    if (fd >= FD_SETSIZE || (player = LIST_PUSH(&server->player_list,
        create_player(fd, &addr))) == NULL) {
        close(fd);
        fprintf(stderr, "error when accepting client.\n");
        return;
    }
    server->maxfd = fd > server->maxfd ? fd : server->maxfd;
    dispatch_event(server, EVT_CONNECT, player);
}

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

void update_server(zappy_server_t *server)
{
    for (player_t *player = server->player_list ; player != NULL ;) {
        if (FD_ISSET(player->client.fd, &server->fdset) &&
            !process_player_input(server, player)) {
            player_t *next = LIST_NEXT(player);
            dispatch_event(server, EVT_DISCONNECT, player);
            LIST_DELETE(&server->player_list, player, free_player);
            player = next;
        } else
            player = LIST_NEXT(player);
    }
}

void server_tick(zappy_server_t *server)
{
    struct timeval timeout = {
        .tv_sec = 0,
        .tv_usec = (__suseconds_t)(1.0 / SERVER_TICKRATE * 1000000),
    };

    FD_ZERO(&server->fdset);
    FD_SET(server->sock, &server->fdset);
    LIST_FOREACH(player, server->player_list, {
        FD_SET(player->client.fd, &server->fdset);
    });
    if (select(server->maxfd + 1, &server->fdset, NULL, NULL, &timeout) == -1) {
        perror("select");
        return;
    }
    if (FD_ISSET(server->sock, &server->fdset))
        accept_client(server);
    else
        update_server(server);
    usleep((__useconds_t)timeout.tv_usec);
}

int server_run(zappy_server_t *server)
{
    struct timespec ts = {0};
    float last_frame = 0.0f;
    float current_time;

    signal(SIGINT, catch_sigint);
    while (is_server_running(NULL)) {
        server_tick(server);
        update_game(server);
        clock_gettime(CLOCK_MONOTONIC, &ts);
        current_time = ((float)ts.tv_sec + (float)ts.tv_nsec / 1000000000.0f);
        server->dt = current_time - last_frame;
        last_frame = current_time;
    }
    return (0);
}
