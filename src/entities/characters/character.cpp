#include "DUNGENGINE/dungengine.hpp"

float Character::baseTurnTime = 100.0f;

Character::Character() : time(0.0f), speed(100.0f)
{
    std::cout << "Character created" << std::endl;
}

void Character::takeTurn()
{
    std::cout << "Character takeTurn" << std::endl;
}

void Character::timeElapse(float time)
{
    this->time += time;
}

void Character::turnElapse()
{
    float timeToElapse = Character::baseTurnTime / this->speed;
    this->timeElapse(timeToElapse);
}

Character::~Character(){}
