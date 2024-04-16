#if !defined(DUNGENGINE_CHARACTERS_PLAYER)
#define DUNGENGINE_CHARACTERS_PLAYER

#include "DUNGENGINE/entities/characters/character.hpp"
#include "DUNGENGINE/utils.hpp"
#include <map>

class Player: public Character
{
private:
    /* data */
public:
    static std::map<char, Vect2> avaliableDirections;

    void interceptInput(char input);
    void playerMove(Vect2 &direction);
    void playerWait();

    Player(/* args */);
    ~Player();

    void takeTurn();
};

#endif // DUNGENGINE_CHARACTERS_PLAYER
