#include <map>
#include <unordered_set>
#include <cassert>

#include "DUNGENGINE/gamemap.hpp"
#include "DUNGENGINE/utils.hpp"
#include "DUNGENGINE/entities/entity.hpp"
#include "DUNGENGINE/globals.hpp"

GameMap::GameMap() : mapSize(DUNGEON_WIDTH, DUNGEON_HEIGHT) {}
GameMap::GameMap(int width, int height) : mapSize(width, height){}

GameMap::~GameMap()
{
    // clear all Entities
    for (std::pair<const Vect2, std::unordered_set<Entity *>> &map_pair : this->positionManager)
    {
        std::unordered_set<Entity*> &positionSet = map_pair.second;
        for (Entity *ptr_entity : positionSet)
        {
            this->entityUnregister(ptr_entity);
            this->entityDestroy(ptr_entity);
        }
        positionSet.clear();
    };

    // clear positionManager
    this->positionManager.clear();
}

bool GameMap::entityRegister(Entity *ptr_entity)
{
    assert(ptr_entity != nullptr && "Pointer must not be null");
    Vect2& position = ptr_entity->position;
    std::unordered_set<Entity *>& entitiesAtPosition = this->positionManager[position];
    entitiesAtPosition.insert(ptr_entity);
    return true;
}

bool GameMap::entityUnregister(Entity *ptr_entity)
{
    assert(ptr_entity != nullptr && "Pointer must not be null");
    Vect2 &position = ptr_entity->position;
    std::unordered_set<Entity *>& entitiesAtPosition = this->positionManager[position];
    entitiesAtPosition.erase(ptr_entity);
    return true;
}

bool GameMap::entityDestroy(Entity *ptr_entity)
{
    delete ptr_entity;
    return true;
}

bool GameMap::entityPlace(Entity *ptr_entity, Vect2 targetPosition)
{
    ptr_entity->position = targetPosition;
    this->entityUnregister(ptr_entity);
    this->entityRegister(ptr_entity);
    return true;
}

bool GameMap::positionIsValid(Vect2 &position)
{
    return position.x >= 0 && position.x < this->mapSize.x && position.y >= 0 && position.y < this->mapSize.y;
}

std::unordered_set<Entity *> &GameMap::getEntitiesAtPosition(Vect2 &position)
{
    return this->positionManager[position];
}

Entity* GameMap::getRenderEntityAtPosition(Vect2 &position)
{
    std::unordered_set<Entity *> &entities = getEntitiesAtPosition(position);
    int currentRenderPriority = 0;
    Entity *currentEntity = nullptr;
    for (Entity *entity : entities)
    {
        if(entity->renderPriority > currentRenderPriority)
        {
            currentRenderPriority = entity->renderPriority;
            currentEntity = entity;
        }
    }
    return currentEntity;
}

void GameMap::testInit()
{}
