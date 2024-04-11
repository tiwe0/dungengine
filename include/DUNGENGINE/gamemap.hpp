#ifndef DUNGENGINE_GAMEMAP
#define DUNGENGINE_GAMEMAP
#include <map>
#include "DUNGENGINE/utils.hpp"
#include "DUNGENGINE/entity.hpp"

class GameMap
{
private:
    /* data */
public:
    static std::map<Vect2, Entity> positionManager;
    static void registerEntity(Vect2 position, Entity entity);
};

#endif