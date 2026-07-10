
#include "RCUT_Renderer.h"
#include "RCUT_Camera.h"
#include "RCUT_RayCaster.h"
#include "RCUT_TileMap.h"

#include <GL/freeglut.h>


namespace RCUTRenderer
{

    static Camera camera;

    static Raycaster raycaster;



    bool Renderer::Initialize(
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



    void Renderer::BeginFrame()
    {
        glClear(
            GL_COLOR_BUFFER_BIT
        );
    }



    void Renderer::RenderMap(
        int* tiles,
        int width,
        int height,
        int tileSize,
        float playerX,
        float playerY,
        float playerAngle
    )
    {

        TileMap map;

        map.tiles = std::vector<int>(tiles, tiles + (width * height));
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



    void Renderer::EndFrame()
    {
        glutSwapBuffers();
    }



    void Renderer::Shutdown()
    {

    }

}