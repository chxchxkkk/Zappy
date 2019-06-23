/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Flag.cpp
*/

#include "Flag.hpp"
#include "TextureLoader.hpp"
#include "Singleton.hpp"
#include "Responsive.hpp"
#include "PlayerManager.hpp"
#include "MapManager.hpp"

const std::vector<sf::Color> Flag::TEAM_COLORS = {
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta,
};

Flag::Flag(int id, const Position &pos, const std::string &teamName) :
    id(id),
    pos(pos)
{
    auto &map = SingleTon<MapManager>::getInstance().getMap();
    const auto &teams = SingleTon<PlayerManager>::getInstance().getTeams();
    auto teamIndex = std::distance(teams.begin(),
                                   std::find(teams.begin(), teams.end(), teamName));
    auto size = Responsive::calcTileSize(map->getWidth(), map->getHeight());
    sprite.setColor(TEAM_COLORS[teamIndex % TEAM_COLORS.size()]);

    sprite.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/flag.png"));
    sprite.setPosition(size * pos.x + size / 3, size * pos.y + size / 3);
    sprite.setScale(size / sprite.getTexture()->getSize().x / 2, size / sprite.getTexture()->getSize().y / 2);
}

void Flag::draw() const
{
    auto &window = SingleTon<sf::RenderWindow>::getInstance();

    window.draw(sprite);
}

int Flag::getId() const
{
    return id;
}
