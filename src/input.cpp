#include "DUNGENGINE/input.hpp"
#include "DUNGENGINE/globals.hpp"

void InputHandler::handleKeyboard(SDL_Event &e)
{
    switch (e.type)
    {
    case SDL_QUIT:
        gQuit = true;
        break;

    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            gPerspectiveDepth+=10;
            printf("increase gPerspectiveDepth: %d\n", gPerspectiveDepth);
            break;
        case SDLK_DOWN:
            gPerspectiveDepth-=10;
            printf("decrease gPerspectiveDepth: %d\n", gPerspectiveDepth);
            break;
        case SDLK_q:
            gQuit = true;
            break;
        case SDLK_w:
            gViewPosition.y -= 10;
            break;
        case SDLK_a:
            gViewPosition.x -= 10;
            break;
        case SDLK_s:
            gViewPosition.y += 10;
            break;
        case SDLK_d:
            gViewPosition.x += 10;
            break;

        default:
            break;
        }

    default:
        break;
    }
}
