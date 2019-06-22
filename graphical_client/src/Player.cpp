/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Player.cpp
*/

#include <utility>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.hpp"
#include "Singleton.hpp"
#include "TextureLoader.hpp"
#include "Tile.hpp"
#include "PlayerManager.hpp"
#include "MapManager.hpp"
#include "Responsive.hpp"

static const std::vector<sf::Color> TEAM_COLORS = {
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta,
};

Player::Player(int id, const Position &pos, Orientation orientation, int level, std::string teamName) :
    id(id),
    pos(pos),
    orientation(orientation),
    level(level),
    teamName(std::move(teamName))
{
    auto &map = SingleTon<MapManager>::getInstance().getMap();
    auto &texture = SingleTon<TextureLoader>::getInstance().getInstance(
        "assets/Character.png");
    size = Responsive::calcTileSize(map->getWidth(), map->getHeight());

    inventory[FOOD] = 0;
    inventory[LINEMATE] = 0;
    inventory[DERAUMERE] = 0;
    inventory[SIBUR] = 0;
    inventory[MENDIANE] = 0;
    inventory[PHIRAS] = 0;
    inventory[THYSTAME] = 0;

    characterSprite.setTexture(texture);
    characterSprite.setPosition(size * pos.x, size * pos.y);
    characterSprite.setScale(Responsive::getScale(size,
                                                  sf::Vector2f(characterSprite.getTexture()->getSize().y,
                                                               characterSprite.getTexture()->getSize().y) * 1.25f));
}

int Player::getId() const
{
    return id;
}

void Player::setPosition(const Position &newPos)
{
    pos.x = newPos.x;
    pos.y = newPos.y;
}

void Player::setOrientation(Orientation newOrientation)
{
    orientation = newOrientation;
}

void Player::setLevel(int newLevel)
{
    level = newLevel;
}

void Player::setResource(Resource type, int quantity)
{
    this->inventory[type] = quantity;
}

void Player::setIncanting(bool newStatus)
{
    this->incanting = newStatus;
}

bool Player::isIncanting() const
{
    return this->incanting;
}

const Position &Player::getPosition() const
{
    return this->pos;
}

void Player::draw()
{
    auto &window = SingleTon<sf::RenderWindow>::getInstance();
    const auto &teams = SingleTon<PlayerManager>::getInstance().getTeams();
    auto teamIndex = std::distance(teams.begin(),
                                   std::find(teams.begin(), teams.end(), this->teamName));
    auto textureSize = characterSprite.getTexture()->getSize().y;

    updateBubble();
    characterSprite.setPosition(size * pos.x + size * (0.25f / 2), size * pos.y + size * (0.25f / 2));
    characterSprite.setTextureRect(
        sf::IntRect((this->orientation - 1) * textureSize, 0, textureSize,
                    textureSize));
    characterSprite.setColor(TEAM_COLORS[teamIndex % TEAM_COLORS.size()]);
    characterSprite.setScale(0.8f, 0.8f);
    window.draw(this->characterSprite);
    if (bubble)
        window.draw(*bubble);
}

const std::map<Resource, int> &Player::getInventory() const
{
    return inventory;
}

int Player::getLevel() const
{
    return level;
}

void Player::addBubble()
{
    bubble = nullptr;
    bubble = std::make_unique<sf::Sprite>();

    bubble->setPosition(characterSprite.getPosition().x + size / 2, characterSprite.getPosition().y - size / 4);
    bubble->setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/bubble.png"));
    bubble->setScale(size / 2 / bubble->getTexture()->getSize().x, size / 2 / bubble->getTexture()->getSize().y);
    prevTime = std::chrono::system_clock::now();
}

void Player::updateBubble()
{
    auto time = std::chrono::system_clock::now();
    auto &playerManager = SingleTon<PlayerManager>::getInstance();
    std::chrono::duration<float> duration = time - prevTime;

    if (duration.count() > 0.5)
        bubble = nullptr;
}
