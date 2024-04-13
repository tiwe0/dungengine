#ifndef DUNGENGINE_ENTITY
#define DUNGENGINE_ENTITY

#include "DUNGENGINE/utils.hpp"

class Entity
{
private:
    /* data */
public:
    Vect2 position;
    Entity(/* args */);
    virtual ~Entity();
};
#endif