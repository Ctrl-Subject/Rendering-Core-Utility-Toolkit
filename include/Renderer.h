#pragma once

#include "RendererAPI.h"
#include "Camera.h"
#include "RayCaster.h"
#include "Sprite.h"
#include "Texture.h"
#include "TileMap.h"

namespace RCUTRenderer
{
    class Renderer_API Renderer
    {
    public:
        static bool Initialize(int width, int height);

        static void Shutdown();

        static void BeginFrame();

        static void EndFrame();

        static void RenderMap(
            int* tiles,
            int width,
            int height,
            int tileSize,
            float playerX,
            float playerY,
            float playerAngle
        );
    };
}