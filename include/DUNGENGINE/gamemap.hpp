#ifndef DUNGENGINE_GAMEMAP
#define DUNGENGINE_GAMEMAP
#include <map>
#include <list>
#include "DUNGENGINE/utils.hpp"
#include "DUNGENGINE/entity.hpp"

struct VectCompare {
    bool operator()(const Vect2& v1, const Vect2& v2)
    {
        if (v1.x == v2.x && v1.y == v2.y)
            return true;
        return false;
    }
};

/// @brief 游戏内部地图，也就是网格地图，地图的坐标均为整数，与渲染地图差一个glyphSize倍数
class GameMap
{
public:
    Vect2 mapSize;

    GameMap();
    ~GameMap();

    std::map<Vect2, std::list<Entity *>, VectCompare> positionManager;
    void registerEntity(Vect2 position, Entity* entity);
};

#endif