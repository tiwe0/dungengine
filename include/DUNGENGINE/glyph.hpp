#ifndef DUNGENGINE_GLYPH
#define DUNGENGINE_GLYPH
#include "SDL2/SDL.h"

/// @brief 渲染使用
class Glyph
{
private:
    /* data */
public:
    /// @brief Glyph大小
    int size;

    /// @brief Glyph字符串
    wchar_t *glyph;

    SDL_Color *colorArray;

    Glyph(const wchar_t *, SDL_Color[]);
    Glyph(const wchar_t *, SDL_Color);
    Glyph(const wchar_t *);
    ~Glyph();
};

#endif