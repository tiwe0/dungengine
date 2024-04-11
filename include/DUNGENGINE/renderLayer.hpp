#ifndef DUNGENGINE_RENDERLAYER
#define DUNGENGINE_RENDERLAYER

#include "DUNGENGINE/painter.hpp"

class Painter;

class RenderLayerAlgorithm
{
public:
    /// @brief 全参数计算透视渲染的位置
    /// @param viewPosition 观测点
    /// @param targetPosition 目标点
    /// @param perspectivePosition 透视点
    /// @param perspectiveDepth 透视深度
    /// @param z z层数
    /// @return Vect2 渲染位置
    static Vect2 computePosition(Vect2 viewPosition, Vect2 targetPosition, Vect2 perspectivePosition, Vect2 viewRenderPosition, int perspectiveDepth, int z);
};

class RenderLayer
{
private:
    int z;
public:
    Painter *painter;
    void drawGlyph(Glyph *glyph, Vect2 position);
    RenderLayer(int z, Painter* painter);
    ~RenderLayer();
};

#endif