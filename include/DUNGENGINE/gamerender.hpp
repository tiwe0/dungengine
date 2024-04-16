#ifndef DUNGENGINE_GAMERENDER
#define DUNGENGINE_GAMERENDER
#include "DUNGENGINE/utils.hpp"
#include "DUNGENGINE/globals.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <map>
#include "entity.hpp"

class GameGlyph
{
public:
    wchar_t *string;
    int length;
    Vect2 size;

    GameGlyph(wchar_t *string);
    ~GameGlyph();
};

class GameRenderLayer
{
private:
    /* data */
public:
    GameRenderLayer(int z);
    ~GameRenderLayer();

    int z;

    void drawGlyph(GameGlyph &glyph, Vect2 targetPosition);
    void drawGlyph(GameGlyph &glyph, Vect2 viewPosition, Vect2 targetPosition, Vect2 viewRenderPosition, Vect2 perspectivePosition, int perspectiveDepth, int z);

    void drawGlyphChar(wchar_t c, Vect2 position, Vect2 size);
};

class GameRender
{
private:
    static GameRender *singleten;

public:
    static bool sdl2_inited;
    static bool sdl2_quited;
    static SDL_Renderer *sdl_renderer;
    static bool gameGlyphCharTextureMapInited;
    static wchar_t *gameGlyphCharSet;
    static TTF_Font *gameGlyphCharFont;
    static GameRenderLayer* gameRenderLayers [NumberOfRenderLayers];
    static std::map<wchar_t, SDL_Texture *> gameGlyphCharTextureMap;

    static void gameSDL2Init();
    static void gameSDL2Quit();

    static void gameTTF_FontInit();
    static void gameGlyphCharTextureMapInit();
    static void gameGlyphCharTextureMapQuit();
    static void gameRenderLayersInit();
    static void gameRenderLayersQuit();

    static void drawGlyph(GameGlyph& glyph, Vect2 position);
    static void drawEntity(Entity &entity);
    static void drawGameMap(GameMap &gamemap);

    GameRender();
    ~GameRender();
};

#endif