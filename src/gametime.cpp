#include "DUNGENGINE/gametime.hpp"

GameTimeManager::GameTimeManager(GameMap& gamemap): gamemap(gamemap)
{}

GameTimeManager::~GameTimeManager(){}

Character* GameTimeManager::characterPop()
{
    if(this->gameTimeManager.empty())
        throw "No character in time queue";
    Character *character = this->gameTimeManager.top();
    this->gameTimeManager.pop();
    return character;
}

void GameTimeManager::characterPush(Character* character)
{
    this->gameTimeManager.push(character);
}

void GameTimeManager::characterDestroy(Character* character)
{
    this->gamemap.entityDestroy(character);
}

void GameTimeManager::turnElapse()
{
    Character *character = this->characterPop();
    character->takeTurn();
    if(character->shouldDead())
    {
        this->characterDestroy(character);
        return;
    }
    this->characterPush(character);
}

void GameTimeManager::timeElapse()
{
    while (gTimeFly)
    {
        this->turnElapse();
    }
}
