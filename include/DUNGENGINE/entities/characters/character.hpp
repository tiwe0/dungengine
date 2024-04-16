#if !defined(DUNGENGINE_ENTITIES_CHARACTER)
#define DUNGENGINE_ENTITIES_CHARACTER
#include "DUNGENGINE/entities/entity.hpp"

class Character: public Entity
{
private:
    /* data */
public:
    static float baseTurnTime;

    float time;
    float speed;

    Character(/* args */);
    ~Character();

    void timeElapse(float time);
    void turnElapse();

    bool shouldDead();

    void virtual takeTurn();
};

#endif // DUNGENGINE_ENTITIES_CHARACTER
