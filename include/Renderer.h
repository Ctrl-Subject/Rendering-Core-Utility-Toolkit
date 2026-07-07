#pragma once

#include "
RCUTRendererAPI.h"
#include "Camera.h"
#include "Raycaster.h"
#include "Sprite.h"
#include "Texture.h"
#include "TileMap.h"


namespace 
RCUTRenderer
{
    //**************************************************
    // 
RCUTRenderer manager
    //
    // Controls 
RCUTRenderer initialization.
    //**************************************************

    class 
RCUTRenderer_API 
RCUTRenderer
    {

        public:

            static bool Initialize();


            static void Shutdown();



            static void BeginFrame();


            static void EndFrame();

    };

}