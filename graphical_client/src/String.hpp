/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** String.hpp
*/

#ifndef ZAPPY_STRING_HPP
#define ZAPPY_STRING_HPP

#include <vector>
#include <string>

class String {
public:
    static std::vector<std::string> split(std::string str, const std::string &sep);
};

#endif
