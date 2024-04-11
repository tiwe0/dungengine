#include "DUNGENGINE/glyph.hpp"

Glyph::Glyph(const wchar_t* s)
{
    this->size = wcslen(s);

    this->glyph = (wchar_t *)(malloc(this->size * sizeof(wchar_t)));
    wcscpy(this->glyph, s);

    this->colorArray = (SDL_Color *)(malloc(this->size * sizeof(SDL_Color)));
    for (int index = 0; index < this->size; index ++)
    {
        this->colorArray[index].r = 0x00;
        this->colorArray[index].g = 0x00;
        this->colorArray[index].b = 0x00;
        this->colorArray[index].a = 0xFF;
    }
}

Glyph::Glyph(const wchar_t *s, SDL_Color colors[])
{
    this->size = wcslen(s);

    int numberOfColor = sizeof(colors) / sizeof(SDL_Color);
    if(numberOfColor != this->size){
        printf("[Glyph]:: init error, size not matched between glyph and color.");
        return;
    }

    this->glyph = (wchar_t *)(malloc(this->size * sizeof(wchar_t)));
    wcscpy(this->glyph, s);

    this->colorArray = (SDL_Color *)(malloc(this->size * sizeof(SDL_Color)));
    for (int index = 0; index < this->size; index ++)
    {
        this->colorArray[index].r = colors[index].r;
        this->colorArray[index].g = colors[index].g;
        this->colorArray[index].b = colors[index].b;
        this->colorArray[index].a = colors[index].a;
    }
}

Glyph::Glyph(const wchar_t *s, SDL_Color color)
{
    this->size = wcslen(s);

    this->glyph = (wchar_t *)(malloc(this->size * sizeof(wchar_t)));
    wcscpy(this->glyph, s);

    this->colorArray = (SDL_Color *)(malloc(this->size * sizeof(SDL_Color)));
    for (int index = 0; index < this->size; index ++)
    {
        this->colorArray[index].r = color.r;
        this->colorArray[index].g = color.g;
        this->colorArray[index].b = color.b;
        this->colorArray[index].a = color.a;
    }
}

Glyph::~Glyph()
{
    free(this->glyph);
    free(this->colorArray);
}