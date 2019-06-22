/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerManager.cpp
*/

#include <algorithm>
#include <iostream>
#include "PlayerManager.hpp"
#include "Singleton.hpp"

void PlayerManager::pnw(const std::vector<std::string> &input)
{
    Position pos(std::stoi(input[1]), std::stoi(input[2]));
    auto orientation = static_cast<Orientation>(std::stoi(input[3]));

    players.emplace_back(parseId(input[0]), pos, orientation, std::stoi(input[4]), input[5]);
}

void PlayerManager::ppo(const std::vector<std::string> &input)
{
    auto &player = getPlayerById(parseId(input[0]));

    player.setPosition(Position(std::stoi(input[1]), std::stoi(input[2])));
    player.setOrientation(static_cast<Orientation>(std::stoi(input[3])));
}

void PlayerManager::plv(const std::vector<std::string> &input)
{
    auto &player = getPlayerById(parseId(input[0]));

    player.setLevel(std::stoi(input[1]));
}

void PlayerManager::pin(const std::vector<std::string> &input)
{
    if (input.size() == 10) {
        auto &player = this->getPlayerById(parseId(input[0]));

        player.setPosition(Position(std::stoi(input[1]), std::stoi(input[2])));
        for (int i = 3; i < 10; ++i) {
            player.setResource(static_cast<Resource >(i - 3), std::stoi(input[i]));
        }
    }
}

Player &PlayerManager::getPlayerById(int id)
{
    return *std::find_if(players.begin(), players.end(), [id](const Player &player) {
        return player.getId() == id;
    });
}

int PlayerManager::parseId(const std::string &s) const
{
    if (s[0] == '#')
        return std::stoi(s.substr(1));
    return std::stoi(s);
}

void PlayerManager::pic(const std::vector<std::string> &input)
{
    if (input.size() >= 4) {
        for (size_t i = 0; i <= input.size() - 4; i++) {
            auto &player = this->getPlayerById(std::stoi(input[i]));

            player.setIncanting(true);
        }
    }
}

std::vector<std::reference_wrapper<Player>> PlayerManager::getPlayersAtPosition(const Position &position)
{
    std::vector<std::reference_wrapper<Player>> player;

    for (auto &it : this->players) {
        if (it.getPosition().x == position.x && it.getPosition().y == position.y)
            player.emplace_back(it);
    }
    return player;
}

void PlayerManager::pie(const std::vector<std::string> &input)
{
    if (input.size() == 3) {
        auto player = this->getPlayersAtPosition(Position(std::stoi(input[0]), std::stoi(input[1])));

        for (auto &it: player) {
            it.get().setIncanting(false);
        }
    }
}

void PlayerManager::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();
    auto view = window.getView();

    for (auto &it : players)
        it.draw();
    if (playerInfo) {
        window.setView(window.getDefaultView());
        playerInfo->draw();
        window.setView(view);
    }
}

void PlayerManager::tna(const std::vector<std::string> &input)
{
    if (!input.empty())
        this->teams.emplace_back(input[0]);
}

const std::vector<std::string> &PlayerManager::getTeams() const
{
    return teams;
}

void PlayerManager::pdi(const std::vector<std::string> &input)
{
    players.erase(std::remove_if(players.begin(), players.end(), [&](const Player &player) {
        if (playerInfo && player.getId() == playerInfo->getPlayerId())
            playerInfo = nullptr;
        return player.getId() == std::stoi(input[0]);
    }), players.end());
}

void PlayerManager::updatePlayerInfo(const Position &selectedTilePosition)
{
    for (auto &player : players) {
        if (player.getPosition() == selectedTilePosition) {
            playerInfo = nullptr;
            playerInfo = std::make_unique<PlayerInfo>(player);
            break;
        }
    }
}

bool PlayerManager::isInfo() const
{
    return playerInfo != nullptr;
}

int PlayerManager::getPlayerInfoId() const
{
    if (playerInfo)
        return playerInfo->getPlayerId();
    return -1;
}

void PlayerManager::removeInfo()
{
    playerInfo = nullptr;
}
