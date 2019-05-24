/*
** EPITECH PROJECT, 2019
** myarpspoof
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <stdlib.h>
#include <netinet/ether.h>

#define CLEAN(f) __attribute__((cleanup(f)))
#define UNUSED __attribute__((unused))

#define ARRAY_LEN(x) ((sizeof(x)/sizeof(*x)) /    \
    ((size_t)(!(sizeof(x) % sizeof(*x)))))

/**
* @brief Copies n bytes from src in a new allocated buffer
* @param src: non-NULL buffer
* @param n: length
* @return a new malloc() allocated buffer of size n or NULL
*/
void *memdup(const void *src, size_t n);

void print_hex(const void *data, size_t n);

void print_mac(const struct ether_addr *addr);

/*
* Cleanup functions
*/
void clean_ptr(void *ptr);
void clean_close(const int *fd_ptr);

/**
* @return a random number between 0.0 and 1.0
*/
float randf(void);
