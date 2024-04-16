#ifndef DUNGENGINE_GAMEMAP
#define DUNGENGINE_GAMEMAP
#include <map>
#include <unordered_set>
#include "DUNGENGINE/utils.hpp"
#include "DUNGENGINE/entities/entity.hpp"
#include "gametime.hpp"

struct VectCompare
{
    bool operator()(const Vect2 &v1, const Vect2 &v2)
    {
        if (v1.x == v2.x && v1.y == v2.y)
            return true;
        return false;
    }
};

/** 游戏内部地图，也就是网格地图。
 * 
 * 地图的坐标均为整数，与渲染地图差一个glyphSize倍数。
 * 由于地图需要记录必要的实体信息，当实体在创建时，需要被注册到地图中；实体在销毁时，需要在地图中查找并销毁。
 * 这些管理行为不应该由实体实现，应该由地图负责。
 * 
 * 接口说明:
 * ## Entity 管理
 * - ~Entity 创建: `entityCreate()`~
 * - Entity 注册: `entityRegister(Entity* entity)`
 * - Entity 注销: `entityUnregidter(Entity* entity)`
 * - Entity 销毁: `entityDestroy(Entity* entity)`
 * - Entity 放置: `entityPlace(Entity* entity, Vect2 position)`
 * ## FOV 视野计算
 * - 计算 Entity 纯视野: `computeFOV(Vect2 position, int distance)`
 * - 计算 Entity 灯光视野: `computeFOVWithLight()`
 * - 计算 Entity 反射视野: `computeFOVWithReflect()`
 * ## 光线计算
 * - 计算 光线范围: `computeLightRange(Vect2 lightPosition, int power)`
 * - 计算 光线强度: `computeLightRange()`
 * ## PathFind 寻路
 * - 计算 不同策略下 两个 Position 之间的路径: `pathBetweenPosition(Vect2 position1, Vect2 position2)`
 */
class GameMap
{
public:
    Vect2 mapSize;
    Vect2 glyphSize;

    std::map<Vect2, std::unordered_set<Entity *>, VectCompare> positionManager;

    GameMap();
    GameMap(int width, int height);
    ~GameMap();

    bool entityRegister(Entity *entity);
    bool entityUnregister(Entity *entity);
    bool entityDestroy(Entity *entity);
    bool entityPlace(Entity *entity, Vect2 position);

    bool positionIsValid(Vect2 &position);

    std::unordered_set<Entity *> &getEntitiesAtPosition(Vect2 &position);
    Entity *getRenderEntityAtPosition(Vect2 &position);

    void testInit();
};

#endif