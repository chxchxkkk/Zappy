/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** String.cpp
*/

#include <iostream>
#include "String.hpp"

std::vector<std::string> String::split(std::string str, const std::string &sep)
{
    std::vector<std::string> strings;
    size_t i;

    do {
        while ((i = str.find(sep)) == 0)
            str = str.substr(sep.length());
        if (i == std::string::npos)
            break;
        strings.push_back(str.substr(0, i));
        str = str.substr(i);
    } while (i != std::string::npos);
    if (!str.empty())
        strings.push_back(str);
    return strings;
}
