#include "RCUT.h"

#include "Camera.h"
#include "Raycaster.h"
#include "TileMap.h"

#include <GL/freeglut.h>


namespace RCUTRenderer
{

    static Renderer::Camera camera;

    static Renderer::Raycaster raycaster;



    bool Initialize(
        int width,
        int height
    )
    {
        raycaster.Initialize(width);

        camera.SetPosition(
            0,
            0
        );

        return true;
    }



    void BeginFrame()
    {
        glClear(
            GL_COLOR_BUFFER_BIT
        );
    }



    void RenderMap(
        int* tiles,
        int width,
        int height,
        int tileSize,
        float playerX,
        float playerY,
        float playerAngle
    )
    {

        Renderer::TileMap map;


        map.tiles = tiles;
        map.width = width;
        map.height = height;
        map.tileSize = tileSize;


        camera.SetPosition(
            playerX,
            playerY
        );


        camera.SetAngle(
            playerAngle
        );


        raycaster.Render(
            map,
            camera,
            512
        );

    }



    void EndFrame()
    {
        glutSwapBuffers();
    }



    void Shutdown()
    {

    }

}