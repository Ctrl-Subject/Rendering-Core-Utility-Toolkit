#pragma once

#include "RendererAPI.h"

namespace Renderer
{

    using TextureID = unsigned int;
    class Renderer_API TextureManager
    {
        public:

            static TextureID Load(
                const char* filename
            );

            static TextureID FromRaw(
                TextureID existing
            );

            static void Destroy(
                TextureID id
            );

            static void Bind(
                TextureID id
            );
    };
}