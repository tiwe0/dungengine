#include "DUNGENGINE/gamerender.hpp"
#include <iostream>

GameGlyph::GameGlyph(wchar_t *string)
{
    this->length = wcslen(this->string);
    this->size.x = GLYPH_SIZE;
    this->size.y = GLYPH_SIZE;

    this->string = new wchar_t[wcslen(string) + 1];
    wcscpy(this->string, string);
}

GameGlyph::~GameGlyph()
{
    delete[] this->string;
}

GameRenderLayer::GameRenderLayer(int z)
{
    this->z = z;
}

GameRenderLayer::~GameRenderLayer()
{
}

void GameRenderLayer::drawGlyph(GameGlyph& glyph, Vect2 targetPosition)
{
    this->drawGlyph(glyph, gViewPosition, targetPosition, gViewRenderPosition, gPerspectivePosition, gPerspectiveDepth, this->z);
}

void GameRenderLayer::drawGlyph(GameGlyph& glyph, Vect2 viewPosition, Vect2 targetPosition, Vect2 viewRenderPosition, Vect2 perspectivePosition, int perspectiveDepth, int z)
    {
        Vect2 targetRelativeToView = targetPosition - viewPosition;
        Vect2 viewRenderRelativeToPerspective = viewRenderPosition - perspectivePosition;
        Vect2 targetRenderTelativeToPerspective = targetRelativeToView + viewRenderRelativeToPerspective;
        float factor = 1 + z * (float)ZDEPTH / (float)perspectiveDepth;
        Vect2 totalOffset = targetRenderTelativeToPerspective * factor;
        Vect2 globalPosition = totalOffset + perspectivePosition;
        this->drawGlyphChar(glyph.string[z], globalPosition, glyph.size);
    }

void GameRenderLayer::drawGlyphChar(wchar_t c, Vect2 position, Vect2 size)
{
    SDL_Rect r;
    r.w = size.x;
    r.h = size.y;
    r.x = position.x;
    r.y = position.y;
    SDL_RenderCopy(gRenderer, GameRender::gameGlyphCharTextureMap[c], NULL, &r);
}

bool GameRender::sdl2_inited = false;
bool GameRender::sdl2_quited = false;
bool GameRender::gameGlyphCharTextureMapInited = false;
wchar_t *GameRender::gameGlyphCharSet = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789·!@#$%^&*()-+_={}[]\\|:\"';?/<>,.";

void GameRender::gameGlyphCharTextureMapInit()
{
    if(!GameRender::sdl2_inited)
        return;

    for (int i = 0; i < wcslen(GameRender::gameGlyphCharSet); i++)
    {
        const wchar_t c = GameRender::gameGlyphCharSet[i];
        if (GameRender::gameGlyphCharTextureMap.find(c) == GameRender::gameGlyphCharTextureMap.end())
        {
            SDL_Surface *s = TTF_RenderGlyph32_Blended(GameRender::gameGlyphCharFont, c, {0x00, 0x00, 0x00, 0xFF});
            if(!s) printf("SDL2 Error: %s\n", TTF_GetError());
            SDL_Texture *t = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
            gameGlyphCharTextureMap.insert(std::pair<wchar_t, SDL_Texture *>(c, t));
            wprintf(L"[GameRender]::registerGlyphCharTexture: %lc\n", c);
        }
    }

    GameRender::gameGlyphCharTextureMapInited = true;
}

void GameRender::gameSDL2Init()
{
    if(GameRender::sdl2_inited)
        return;

    if(SDL_Init(SDL_INIT_VIDEO < 0))
    {
        printf("sdl2 init failed: %s\n", SDL_GetError());
        exit(-1);
    }

    TTF_Init();
    GameRender::gameTTF_FontInit();
    GameRender::gameGlyphCharTextureMapInit();

    gWindow = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if(!gWindow)
    {
        printf("sdl2 window init failed: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(-1);
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!gRenderer)
    {
        printf("sdl2 window init failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(gWindow);
        TTF_Quit();
        SDL_Quit();
        exit(-1);
    }

    GameRender::sdl2_inited = true;
}

void GameRender::gameSDL2Quit()
{
    if(GameRender::sdl2_quited)
        return;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gameGlyphCharTextureMapQuit();
    TTF_Quit();
    SDL_Quit();

    GameRender::sdl2_quited = true;
}

void GameRender::gameGlyphCharTextureMapQuit()
{
    for (int i = 0; i < wcslen(gameGlyphCharSet); i++)
    {
        wchar_t c = gameGlyphCharSet[i];
        if(gameGlyphCharTextureMap.find(c) != gameGlyphCharTextureMap.end())
        {
            SDL_DestroyTexture(gameGlyphCharTextureMap[c]);
            gameGlyphCharTextureMap.erase(c);
            wprintf(L"[GameRender]::destroyGlyph: %lc\n", c);
        }
    }
}

void GameRender::gameTTF_FontInit()
{
    if(GameRender::gameGlyphCharFont!=nullptr)
        return;
    GameRender::gameGlyphCharFont = TTF_OpenFont(FONT_PATH, GLYPH_SIZE);
    if(!GameRender::gameGlyphCharFont)
    {
        printf("Unable to load font: '%s'!\n"
                "SDL2_TTF Error: %s\n",
                FONT_PATH, TTF_GetError());
    }
}

void GameRender::gameRenderLayersInit()
{
    for (int i = 0; i < NumberOfRenderLayers; i++)
    {
        gameRenderLayers[i] = new GameRenderLayer(i);
    }
}

void GameRender::gameRenderLayersQuit()
{
    for (int i = 0; i < NumberOfRenderLayers; i++)
    {
        delete gameRenderLayers[i];
    }
}

void GameRender::drawGlyph(GameGlyph& glyph, Vect2 position)
{
    for (int i = 0; i < NumberOfRenderLayers; i++)
    {
        gameRenderLayers[i]->drawGlyph(glyph, position);
    }
}

void GameRender::drawEntity(Entity& entity)
{
    GameGlyph& glyph = entity.glyph;
    Vect2 &position = entity.position;
    drawGlyph(glyph, position);
}

void GameRender::drawGameMap(GameMap &gamemap)
{
    int width_in_grid = SCREEN_WIDTH / GLYPH_SIZE / 2;
    int height_in_grid = SCREEN_HEIGHT / GLYPH_SIZE / 2;
    Vect2 gGamePosition = gViewPosition / GLYPH_SIZE;
    for (int row = -height_in_grid; row < height_in_grid + 1; row++)
    {
        for (int col = -width_in_grid; col < width_in_grid + 1; col++)
        {
            Vect2 offset = Vect2(col, row);
            Vect2 gamePosition = gGamePosition + offset;
            Entity *renderEntity = gamemap.getRenderEntityAtPosition(gamePosition);
            if(renderEntity == nullptr) break;
            drawEntity(*renderEntity);
        }
    }
}

GameRender::GameRender()
{
    gameSDL2Init();
}

GameRender::~GameRender()
{
    gameSDL2Quit();
}
