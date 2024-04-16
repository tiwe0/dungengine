#ifndef DUNGENGINE_INPUT
#define DUNGENGINE_INPUT

#include "SDL2/SDL.h"

class InputHandler
{
public:
    static void handleKeyboard(SDL_Event &e);
    static void handleInput();
};

#endif