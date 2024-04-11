#ifndef DUNGENGINE_PAINTER
#define DUNGENGINE_PAINTER

#include <map>
#include "SDL2/SDL.h"
#include "DUNGENGINE/dungengine.hpp"

class RenderLayer;

class Painter
{
private:
    /* data */
    SDL_Renderer* renderer;
public:
    static void sdl_init();
    static void sdl_quit();

    static wchar_t *chars;
    static std::map<wchar_t, SDL_Texture*> glyphMap;

    static void initGlyphMap();
    static void registerCharTexture(const wchar_t);
    static void destroyGlyphMap();

    void initRenderLayers();
    void destroyRenderLayers();

    RenderLayer* renderLayers[NumberOfRenderLayers];

    void drawGlyphChar(const wchar_t c, int x, int y, int w, int h);
    void drawGlyphChar(const wchar_t c, Vect2 position, Vect2 size);

    void drawGlyph(Glyph *glyph, Vect2 position);

    Painter(SDL_Renderer *renderer);
    ~Painter();
};

#endif