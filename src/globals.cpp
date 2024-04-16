#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "DUNGENGINE/utils.hpp"
#include "DUNGENGINE/globals.hpp"

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

TTF_Font *gGlyphFont;

Vect2 gViewPosition = Vect2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
Vect2 gPerspectivePosition = Vect2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
Vect2 gViewRenderPosition = Vect2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

Vect2 gGlyphSize = Vect2(GLYPH_SIZE, GLYPH_SIZE);
int gPerspectiveDepth = PERSPECTIVE_DEPTH;

bool gQuit = false;
bool gTimeFly = false;
bool gTurnShouldElapse = false;
