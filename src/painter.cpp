#include <stdio.h>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "DUNGENGINE/globals.hpp"
#include "DUNGENGINE/renderLayer.hpp"
#include "DUNGENGINE/painter.hpp"
#include "DUNGENGINE/utils.hpp"

wchar_t* Painter::chars = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789·!@#$%^&*()-+_={}[]\\|:\"';?/<>,.";
std::map<wchar_t, SDL_Texture *> Painter::glyphMap;

void Painter::drawGlyph(Glyph *glyph, Vect2 position)
{
    for (int index = 0; index < glyph->size; index++)
    {
        this->renderLayers[index]->drawGlyph(glyph, position);
    }
}

void Painter::drawGlyphChar(const wchar_t c, int x, int y, int w, int h)
{
    SDL_Rect r;
    r.w = w;
    r.h = h;
    r.x = x;
    r.y = y;
    SDL_RenderCopy(gRenderer, glyphMap[c], NULL, &r);
}

void Painter::drawGlyphChar(const wchar_t c, Vect2 position, Vect2 size)
{
    Painter::drawGlyphChar(c, position.x, position.y, size.x, size.y);
}

void Painter::initRenderLayers()
{
    for (int z = 0; z < NumberOfRenderLayers; z++)
    {
        this->renderLayers[z] = new RenderLayer(z, this);
        printf("[Painter]::initRenderLayers: %d\n", z);
    }
}

void Painter::destroyRenderLayers()
{
    for (int z = 0; z < NumberOfRenderLayers; z++)
    {
        this->renderLayers[z]->~RenderLayer();
        printf("[Painter]::destroyRenderLayers: %d\n", z);
    }
}

void Painter::destroyGlyphMap()
{
    for (int i = 0; i < wcslen(chars); i++)
    {
        if (glyphMap.find(chars[i])!=glyphMap.end())
        {
            SDL_Texture *t = glyphMap[chars[i]];
            SDL_DestroyTexture(t);
            glyphMap.erase(chars[i]);
            wprintf(L"[Painter]::destroyGlyph: %lc\n", chars[i]);
        }
    }
}

void Painter::registerCharTexture(const wchar_t c)
{
    SDL_Surface *s = TTF_RenderGlyph32_Blended(gGlyphFont, c, {0x00, 0x00, 0x00, 0xFF});
    if(!s)
    {
        printf("SDL2 Error: %s\n", TTF_GetError());
    }
    SDL_Texture *t = SDL_CreateTextureFromSurface(gRenderer, s);
    SDL_FreeSurface(s);
    glyphMap.insert(std::pair<wchar_t, SDL_Texture *>(c, t));
    wprintf(L"[Painter]::registerCharTexture: %lc\n", c);
}

void Painter::initGlyphMap()
{
    for (int i = 0; i < wcslen(chars); i++)
    {
        if (glyphMap.find(chars[i])==glyphMap.end()){
            Painter::registerCharTexture(chars[i]);
        }
    }
}

void Painter::sdl_init()
{
    // init sdl2
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("sdl2 init failed: %s", SDL_GetError());
    }

    // init sdl_ttf
    TTF_Init();
}

void Painter::sdl_quit()
{
    TTF_Quit();
    SDL_Quit();
}

Painter::Painter(SDL_Renderer* renderer)
{
    Painter::initGlyphMap();
    this->initRenderLayers();
    this->renderer = renderer;
}

Painter::~Painter()
{
    Painter::destroyGlyphMap();
    this->destroyRenderLayers();
}
