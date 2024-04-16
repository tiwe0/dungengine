#include "DUNGENGINE/entities/characters/player.hpp"
#include <iostream>

std::map<char, Vect2> Player::avaliableDirections = {
    {'h', Vect2(-1, 0)},
    {'j', Vect2(0, 1)},
    {'k', Vect2(0, -1)},
    {'l', Vect2(1, 0)},
    {'y', Vect2(-1, -1)},
    {'u', Vect2(1, -1)},
    {'b', Vect2(-1, 1)},
    {'n', Vect2(1, 1)},
};

void Player::playerMove(Vect2 &direction)
{
    GameMap &gamemap = this->gamemap;
    Vect2 targetPosition = this->position + direction;
    if (gamemap.positionIsValid(targetPosition))
    {
        gamemap.entityPlace(this, targetPosition);
    }
}

void Player::playerWait()
{
    return;
}

void Player::interceptInput(char input)
{
    switch (input)
    {
    // move
    case 'h':
    case 'j':
    case 'k':
    case 'l':
    case 'y':
    case 'u':
    case 'b':
    case 'n':
        Vect2 &targetDirection = Player::avaliableDirections[input];
        this->playerMove(targetDirection);
        break;

    // wait
    case '.':
        break;

    default:
        std::cout << "Player got input key: " << input << std::endl;
        return;
    }
    this->turnElapse();
}

Player::Player() {}
void Player::takeTurn()
{
    char c;
    std::cin >> c;
    this->interceptInput(c);
}

Player::~Player(){}
