#pragma once

#ifdef RCUT_RENDERER_EXPORTS
#define RCUT_API __declspec(dllexport)
#else
#define RCUT_API __declspec(dllimport)
#endif


namespace RCUTRenderer
{

    //**************************************************
    // Start renderer
    //
    // Creates internal renderer objects and prepares
    // OpenGL resources.
    //**************************************************

    RCUT_API bool Initialize(
        int width,
        int height
    );



    //**************************************************
    // Start drawing frame
    //
    // Clears the screen and prepares rendering.
    //**************************************************

    RCUT_API void BeginFrame();



    //**************************************************
    // Render the tile map
    //
    // tiles:
    //     Array containing your map data
    //
    // width / height:
    //     Map dimensions
    //
    // tileSize:
    //     Size of each tile in pixels
    //
    // playerX/playerY:
    //     Player world position
    //
    // playerAngle:
    //     Player rotation
    //**************************************************

    RCUT_API void RenderMap(
        int* tiles,
        int width,
        int height,
        int tileSize,
        float playerX,
        float playerY,
        float playerAngle
    );



    //**************************************************
    // Finish drawing frame
    //
    // Swaps OpenGL buffers.
    //**************************************************

    RCUT_API void EndFrame();



    //**************************************************
    // Shutdown renderer
    //
    // Frees renderer resources.
    //**************************************************

    RCUT_API void Shutdown();

}