#pragma once

//=====================================================
// RCUT - Rendering Core Utility Toolkit
// Public API
//=====================================================

#ifdef _WIN32
    #ifdef RCUT_RENDERER_EXPORTS
        #define RCUT_API __declspec(dllexport)
    #else
        #define RCUT_API __declspec(dllimport)
    #endif
#else
    #define RCUT_API
#endif

namespace RCUTRenderer
{
    //=================================================
    // Engine Lifetime
    //=================================================

    RCUT_API bool Initialize(
        int screenWidth,
        int screenHeight
    );

    RCUT_API void Shutdown();

    //=================================================
    // Frame
    //=================================================

    RCUT_API void BeginFrame();

    RCUT_API void EndFrame();

    //=================================================
    // Camera
    //=================================================

    RCUT_API void SetCameraPosition(
        float x,
        float y
    );

    RCUT_API void SetCameraAngle(
        float angle
    );

    RCUT_API void SetCameraFOV(
        float fov
    );

    //=================================================
    // Map Rendering
    //=================================================

    RCUT_API void RenderMap(
        const int* tiles,
        int mapWidth,
        int mapHeight,
        int tileSize
    );

    //=================================================
    // Sprites
    //=================================================

    RCUT_API void ClearSprites();

    RCUT_API void AddSprite(
        float x,
        float y,
        float size,
        unsigned textureID
    );

    RCUT_API void RenderSprites();

    //=================================================
    // Textures
    //=================================================

    RCUT_API unsigned LoadTexture(
        const char* filename
    );

    RCUT_API void DestroyTexture(
        unsigned textureID
    );
}