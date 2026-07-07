#pragma once

#include "RendererAPI.h"
#include "Camera.h"
#include "Raycaster.h"
#include "Sprite.h"
#include "Texture.h"
#include "TileMap.h"


namespace RCUTRenderer
{
    //**************************************************
    // Renderer manager
    //
    // Controls Renderer initialization.
    //**************************************************

    class Renderer_API Renderer
    {

        public:

            static bool Initialize();


            static void Shutdown();



            static void BeginFrame();


            static void EndFrame();

    };

}