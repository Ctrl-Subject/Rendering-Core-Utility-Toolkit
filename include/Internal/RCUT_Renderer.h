#pragma once

#include "RCUT_RendererAPI.h"
#include "RCUT_Camera.h"
#include "RCUT_RayCaster.h"
#include "RCUT_Sprite.h"
#include "RCUT_Texture.h"
#include "RCUT_TileMap.h"

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