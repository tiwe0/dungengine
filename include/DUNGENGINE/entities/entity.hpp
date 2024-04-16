#ifndef DUNGENGINE_ENTITY
#define DUNGENGINE_ENTITY

#include "DUNGENGINE/utils.hpp"

#include "DUNGENGINE/entities/characters/character.hpp"
#include "DUNGENGINE/entities/characters/player.hpp"
#include "DUNGENGINE/gamemap.hpp"
#include "DUNGENGINE/glyph.hpp"
#include "DUNGENGINE/gamerender.hpp"

/// @brief 实体，是游戏中的主要组成部分
class Entity
{
private:
    /* data */
public:
    /// @brief 血量，通常血量为0的时候该实体需要销毁清理
    int hp;
    /// @brief 渲染优先级，多个实体重复在统一位置时，优先级高的会渲染
    int renderPriority;
    /// @brief 位置，通常用来给游戏地图检索使用
    Vect2 position;
    /// @brief 实体所存在的游戏地图
    GameMap &gamemap;
    /// @brief 表示该实体的 Glyph
    GameGlyph &glyph;

    Entity(GameMap& gamemap, GameGlyph& glyph);
    virtual ~Entity();
};
#endif