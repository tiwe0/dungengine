#include "DUNGENGINE/input.hpp"
#include "DUNGENGINE/globals.hpp"

void InputHandler::handleKeyboard(SDL_Event &e)
{
    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
        gPerspectiveDepth += GLYPH_SIZE;
        printf("increase gPerspectiveDepth: %d\n", gPerspectiveDepth);
        break;
    case SDLK_DOWN:
        gPerspectiveDepth -= GLYPH_SIZE;
        printf("decrease gPerspectiveDepth: %d\n", gPerspectiveDepth);
        break;
    case SDLK_q:
        gQuit = true;
        break;
    case SDLK_w:
        gViewPosition.y -= GLYPH_SIZE;
        break;
    case SDLK_a:
        gViewPosition.x -= GLYPH_SIZE;
        break;
    case SDLK_s:
        gViewPosition.y += GLYPH_SIZE;
        break;
    case SDLK_d:
        gViewPosition.x += GLYPH_SIZE;
        break;

    default:
        break;
    }
}

void InputHandler::handleInput()
{
    SDL_Event e;
    SDL_WaitEvent(&e);

    switch (e.type)
    {
    case SDL_KEYDOWN:
        handleKeyboard(e);
        gPlayerTurnShouldElapse = true;
        break;

    case SDL_QUIT:
        gQuit = true;

    default:
        break;
    }
}
