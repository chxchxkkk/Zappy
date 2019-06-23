/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Egg.cpp
*/

#include "Egg.hpp"
#include "Singleton.hpp"
#include "PlayerManager.hpp"
#include "Responsive.hpp"
#include "MapManager.hpp"

const std::vector<sf::Color> Egg::TEAM_COLORS = {
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta,
};

Egg::Egg(int id, const Position &pos, const std::string &teamName) :
    id(id),
    pos(pos)
{
    auto &map = SingleTon<MapManager>::getInstance().getMap();
    const auto &teams = SingleTon<PlayerManager>::getInstance().getTeams();
    auto teamIndex = std::distance(teams.begin(),
                                   std::find(teams.begin(), teams.end(), teamName));
    auto size = Responsive::calcTileSize(map->getWidth(), map->getHeight());
    sprite.setColor(TEAM_COLORS[teamIndex % TEAM_COLORS.size()]);

    sprite.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/egg.png"));
    sprite.setPosition(size * pos.x + size / 3, size * pos.y + size / 3);
    sprite.setScale(size / sprite.getTexture()->getSize().x / 2, size / sprite.getTexture()->getSize().y / 2);
}

void Egg::draw() const
{
    auto &window = SingleTon<sf::RenderWindow>::getInstance();

    window.draw(sprite);
}
