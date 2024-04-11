#include <stdio.h>
#include "DUNGENGINE/globals.hpp"
#include "DUNGENGINE/painter.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    Painter::sdl_init();

    // init window
    gWindow = SDL_CreateWindow("Dungengine GUI",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!gWindow)
    {
        printf("Window could not be created!\n"
               "SDL2 Error: %s\n",
               SDL_GetError());
        Painter::sdl_quit();
        return 0;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!gRenderer)
    {
        printf("Renderer could not created!\n"
                "SDL2 Error: %s\n",
                SDL_GetError());
        SDL_DestroyWindow(gWindow);
        return 0;
    }

    gGlyphFont = TTF_OpenFont(FONT_PATH, GLYPH_SIZE);
    if(!gGlyphFont)
    {
        printf("Unable to load font: '%s'!\n"
                "SDL2_TTF Error: %s\n",
                FONT_PATH, TTF_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        return 0;
    }

    // core code
    Painter* painter = new Painter(gRenderer);

    while(!gQuit)
    {
        SDL_Event e;

        SDL_WaitEvent(&e);

        InputHandler::handleKeyboard(e);

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        SDL_RenderClear(gRenderer);

        Glyph glyph = Glyph(L"·····*");
        Glyph viewGlyph = Glyph(L"·");

        painter->drawGlyph(&glyph, Vect2(300, 200));
        painter->drawGlyph(&glyph, Vect2(500, 200));
        painter->drawGlyph(&glyph, Vect2(500, 400));
        painter->drawGlyph(&viewGlyph, gViewPosition);

        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyRenderer(gRenderer);

    SDL_DestroyWindow(gWindow);

    painter->~Painter();

    Painter::sdl_quit();

    return 0;
}
