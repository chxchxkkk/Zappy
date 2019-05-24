/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <netinet/ip.h>

#define TCP_MAX_CONNECTION  1000

int create_server_tcp_socket(in_port_t port);
