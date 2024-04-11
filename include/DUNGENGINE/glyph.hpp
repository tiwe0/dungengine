#ifndef DUNGENGINE_GLYPH
#define DUNGENGINE_GLYPH
#include "SDL2/SDL.h"

class Glyph
{
private:
    /* data */
public:
    int size;
    wchar_t *glyph;
    SDL_Color *colorArray;

    Glyph(const wchar_t *, SDL_Color[]);
    Glyph(const wchar_t *, SDL_Color);
    Glyph(const wchar_t *);
    ~Glyph();
};

#endif