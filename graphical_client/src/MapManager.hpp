/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include "Map.hpp"

class MapManager {
    public:
        MapManager() = default;
        void msz(const std::vector<std::string> &);
        void bct(const std::vector<std::string> &args);
        std::unique_ptr<Map> &getMap();

    private:
        std::unique_ptr<Map> map = nullptr;
        static std::pair<int, int> parsePosition(const std::vector<std::string> &pos);

};

