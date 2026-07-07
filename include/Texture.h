#pragma once

#include "
RCUTRendererAPI.h"

namespace 
RCUTRenderer
{

    using TextureID = unsigned int;
    class 
RCUTRenderer_API TextureManager
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