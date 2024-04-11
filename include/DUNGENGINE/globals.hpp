#ifndef DUNGENGINE_GLOBALS
#define DUNGENGINE_GLOBALS

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "DUNGENGINE/utils.hpp"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PERSPECTIVE_DEPTH 800

#define ZDEPTH 32

#define GLYPH_SIZE 32
#define FONT_PATH "/Users/ivory/Project/dungengine/assets/font/PressStart2P-Regular.ttf"

#define NumberOfRenderLayers 7

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

extern TTF_Font *gGlyphFont;
extern Vect2 gViewPosition;
extern Vect2 gViewRenderPosition;
extern Vect2 gPerspectivePosition;
extern Vect2 gGlyphSize;
extern int gPerspectiveDepth;
extern bool gQuit;

#endif