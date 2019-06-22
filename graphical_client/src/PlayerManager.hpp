/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerManager.hpp
*/

#ifndef ZAPPY_PLAYERMANAGER_HPP
#define ZAPPY_PLAYERMANAGER_HPP

#include <memory>
#include <vector>
#include "Player.hpp"
#include "PlayerInfo.hpp"

class PlayerManager {
public:
    PlayerManager() = default;
    Player &getPlayerById(int id);

    void ppo(const std::vector<std::string> &input);
    void pnw(const std::vector<std::string> &input);
    void plv(const std::vector<std::string> &input);
    void pin(const std::vector<std::string> &input);
    void pic(const std::vector<std::string> &input);
    void pie(const std::vector<std::string> &input);
    void tna(const std::vector<std::string> &input);
    void pdi(const std::vector<std::string> &input);

    void draw();
    const std::vector<std::string> &getTeams() const;
    int parseId(const std::string &s) const;
    void updatePlayerInfo(const Position &selectedTilePosition);
    bool isInfo() const;
    int getPlayerInfoId() const;

private:
    std::unique_ptr<PlayerInfo> playerInfo;
    std::vector<std::string> teams;
    std::vector<std::reference_wrapper<Player>> getPlayersAtPosition(
        const Position &position);
    std::vector<Player> players;
};

#endif
