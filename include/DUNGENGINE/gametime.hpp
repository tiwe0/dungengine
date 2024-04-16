#if !defined(DUNGENGINE_GAMETIME)
#define DUNGENGINE_GAMETIME

#include <queue>
#include <vector>

#include "DUNGENGINE/entities/characters/character.hpp"
#include "DUNGENGINE/globals.hpp"

/// @brief GameTimeManager 的最小堆排序函数
struct CompareCharacter {
    bool operator()(const Character* lhs, const Character* rhs) const
    {
        return lhs->time > rhs->time;
    }
};

/// @brief 游戏的时间管理器
class GameTimeManager
{
public:
    /// @brief 内部存储的最小堆
    std::priority_queue<Character *, std::vector<Character *>, CompareCharacter> gameTimeManager;

    /// @brief 游戏地图引用，主要用来清理死亡实体
    GameMap &gamemap;

    GameTimeManager(GameMap& gamemap);
    ~GameTimeManager();

    /// @brief 从时间队列中挑选时间最小的人物实体
    /// @return 目标人物实体的指针
    Character *characterPop();

    /// @brief 将人物实体放入时间队列
    /// @param character 指向人物实体的指针
    void characterPush(Character *character);

    /// @brief 清除人物实体，委托给 gammap 负责；
    /// @param character 指向人物实体的指针； 
    void characterDestroy(Character* character);

    /// @brief 让时间前进一回合；
    void turnElapse();

    /// @brief 让时间持续流动
    void timeElapse();
};

#endif // DUNGENGINE_GAMETIME
