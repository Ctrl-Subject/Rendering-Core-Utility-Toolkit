#pragma once

#include "
RCUTRendererAPI.h"
#include "Camera.h"
#include "Raycaster.h"
#include "Texture.h"
#include <vector>

namespace 
RCUTRenderer
{
    struct Sprite
    {
        TextureID texture;

        float x;
        float y;

        float width;
        float height;

        float scale;

        Sprite()
        {
            texture = 0;

            x = 0;
            y = 0;

            width = 64;
            height = 64;

            scale = 1.0f;
        }
    };

    class 
RCUTRenderer_API Sprite
RCUTRenderer
    {
    private:

        std::vector<Sprite> sprites;

    public:

        void Clear();

        void Add(
            const Sprite& sprite
        );

        void Render(
            const Camera& camera,
            const Raycaster& raycaster,
            int screenWidth,
            int screenHeight
        );
    };
}