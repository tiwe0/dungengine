#include "DUNGENGINE/utils.hpp"
#include "DUNGENGINE/renderLayer.hpp"
#include "DUNGENGINE/globals.hpp"
#include "DUNGENGINE/glyph.hpp"
#include "DUNGENGINE/painter.hpp"

Vect2 RenderLayerAlgorithm::computePosition(Vect2 viewPosition, Vect2 targetPosition, Vect2 viewRenderPosition, Vect2 perspectivePosition, int perspectiveDepth, int z)
{
    Vect2 targetRelativeToView = targetPosition - viewPosition;
    Vect2 viewRenderRelativeToPerspective = viewRenderPosition - perspectivePosition;
    Vect2 targetRenderTelativeToPerspective = targetRelativeToView + viewRenderRelativeToPerspective;
    float factor = 1 + z * (float)ZDEPTH / (float)perspectiveDepth;
    printf("z: %d: factor: %f\n", z, factor);
    Vect2 totalOffset = targetRenderTelativeToPerspective * factor;
    return totalOffset + perspectivePosition;
}

void RenderLayer::drawGlyph(Glyph* glyph, Vect2 position)
{
    wchar_t c = glyph->glyph[this->z];
    SDL_Color color = glyph->colorArray[this->z];
    Vect2 renderPosition = RenderLayerAlgorithm::computePosition(
        gViewPosition, position, gViewRenderPosition, gPerspectivePosition,
        gPerspectiveDepth, this->z
    );
    wprintf(L"[RenderLayer %d] render glyph: %lc at position (%d, %d)\n", this->z, c, renderPosition.x, renderPosition.y);
    this->painter->drawGlyphChar(c, renderPosition, gGlyphSize);
}

RenderLayer::RenderLayer(int z, Painter* painter)
{
    this->z = z;
    this->painter = painter;
}

RenderLayer::~RenderLayer()
{
}
