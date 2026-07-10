#pragma once

#include "RCUT_RendererAPI.h"

#include "RCUT_Camera.h"
#include "RCUT_TileMap.h"

namespace RCUTRenderer
{
    class Renderer_API Raycaster
    {
        private:
            float* depthBuffer;

            int screenWidth;

        public:
            Raycaster();

            ~Raycaster();

            void Initialize(
                int width
            );

            void Render(
                const TileMap& map,
                const Camera& camera,
                int screenHeight
            );

            float GetDepth(
                int x
            ) const;
    };
}