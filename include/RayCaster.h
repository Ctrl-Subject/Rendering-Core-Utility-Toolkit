#pragma once

#include "
RCUTRendererAPI.h"

#include "Camera.h"
#include "TileMap.h"

namespace 
RCUTRenderer
{
    class 
RCUTRenderer_API Raycaster
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