#include <stdio.h>
#include "DUNGENGINE/dungengine.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    // core code
    GameRender *gameRender = new GameRender();
    GameMap *gameMap = new GameMap();
    GameTimeManager *gameTimeManager = new GameTimeManager(*gameMap);

    gameMap->testInit();

    while(!gQuit)
    {
        InputHandler::handleInput();

        if (gPlayerTurnShouldElapse)
        {
            gameTimeManager->turnElapse();
        }
        gameRender->drawGameMap(*gameMap);
        gPlayerTurnShouldElapse = false;
    }

    delete gameRender;
    delete gameMap;
    delete gameTimeManager;

    return 0;
}
