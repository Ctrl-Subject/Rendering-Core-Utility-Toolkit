#pragma once

#ifdef RCUT_
RCUTRenderer_EXPORTS
#define RCUT_API __declspec(dllexport)
#else
#define RCUT_API __declspec(dllimport)
#endif


namespace RCUT
RCUTRenderer
{

    //**************************************************
    // Starts the 
RCUTRenderer
    //
    // width  = screen width
    // height = screen height
    //
    // Returns false if initialization fails
    //**************************************************

    RCUT_API bool Initialize(
        int width,
        int height
    );


    //**************************************************
    // Starts a frame
    //
    // Clears buffers and prepares rendering
    //**************************************************

    RCUT_API void BeginFrame();



    //**************************************************
    // Draws the raycast world
    //
    // tiles     = map array
    // width     = map width in tiles
    // height    = map height in tiles
    // tileSize  = size of each tile
    //
    // playerX/Y = player world position
    // angle     = player looking direction
    //**************************************************

    RCUT_API void RenderMap(
        int* tiles,
        int width,
        int height,
        int tileSize,
        float playerX,
        float playerY,
        float angle
    );



    //**************************************************
    // Draw a sprite
    //
    // textureID = OpenGL texture ID
    // x/y       = world position
    // width     = sprite width
    // height    = sprite height
    //**************************************************

    RCUT_API void RenderSprite(
        unsigned int textureID,
        float x,
        float y,
        float width,
        float height
    );



    //**************************************************
    // Ends the frame
    //
    // Used for any 
RCUTRenderer cleanup
    //**************************************************

    RCUT_API void EndFrame();



    //**************************************************
    // Frees 
RCUTRenderer memory
    //**************************************************

    RCUT_API void Shutdown();

}