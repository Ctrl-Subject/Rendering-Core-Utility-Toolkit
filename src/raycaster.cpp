#include "Raycaster.h"

#include <GL/freeglut.h>
#include <cmath>


#define PI 3.1415926535f


namespace RCUTRenderer
{


//**************************************************
// Constructor
//**************************************************

Raycaster::Raycaster()
{
    depthBuffer = nullptr;
    screenWidth = 0;
}



//**************************************************
// Destructor
//**************************************************

Raycaster::~Raycaster()
{
    delete[] depthBuffer;
}



//**************************************************
// Setup depth buffer
//**************************************************

void Raycaster::Initialize(int width)
{
    screenWidth = width;

    delete[] depthBuffer;

    depthBuffer = new float[width];


    for(int i = 0; i < width; i++)
        depthBuffer[i] = 0;
}



//**************************************************
// Render world
//**************************************************

void Raycaster::Render(
    const TileMap& map,
    const Camera& camera,
    int screenHeight
)
{
    float rayAngle = camera.GetAngle() - camera.GetFOV()/2;
    float angleStep = camera.GetFOV()/screenWidth;


    for(int ray = 0; ray < screenWidth; ray++)
    {

        float rayDirX = cos(rayAngle);
        float rayDirY = sin(rayAngle);


        int mapX = camera.GetX()/map.tileSize;
        int mapY = camera.GetY()/map.tileSize;


        float deltaDistX = fabs(1.0f/rayDirX);
        float deltaDistY = fabs(1.0f/rayDirY);


        int stepX;
        int stepY;

        float sideDistX;
        float sideDistY;



        //**************************************************
        // X stepping
        //**************************************************

        if(rayDirX < 0)
        {
            stepX = -1;

            sideDistX =
                (camera.GetX()/map.tileSize - mapX)
                *
                deltaDistX;
        }

        else
        {
            stepX = 1;

            sideDistX =
                (mapX + 1.0f - camera.GetX()/map.tileSize)
                *
                deltaDistX;
        }



        //**************************************************
        // Y stepping
        //**************************************************

        if(rayDirY < 0)
        {
            stepY = -1;

            sideDistY =
                (camera.GetY()/map.tileSize - mapY)
                *
                deltaDistY;
        }

        else
        {
            stepY = 1;

            sideDistY =
                (mapY + 1.0f - camera.GetY()/map.tileSize)
                *
                deltaDistY;
        }



        int hit = 0;
        int side = 0;
        int hitType = 0;



        //**************************************************
        // DDA
        //**************************************************

        while(!hit)
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }

            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }



            int tile = map.GetTile(
                mapX,
                mapY
            );


            if(tile != 0)
            {
                hit = 1;
                hitType = tile;
            }
        }



        //**************************************************
        // Distance calculation
        //**************************************************

        float distance =
            (side == 0 ?
            sideDistX - deltaDistX :
            sideDistY - deltaDistY);


        distance *= map.tileSize;


        // Fish eye correction

        distance *= cos(
            camera.GetAngle() - rayAngle
        );


        depthBuffer[ray] = distance;



        //**************************************************
        // Wall height
        //**************************************************

        float lineH =
            (map.tileSize * screenHeight)
            /
            (distance + 0.0001f);


        float lineO =
            (screenHeight/2)
            -
            (lineH/2);



        //**************************************************
        // Wall colours
        //**************************************************

        if(hitType == 2)
            glColor3f(0,0,1);

        else if(side == 0)
            glColor3f(1,0,0);

        else
            glColor3f(0.7f,0,0);



        glBegin(GL_LINES);

            glVertex2f(
                ray,
                lineO
            );

            glVertex2f(
                ray,
                lineO + lineH
            );

        glEnd();



        rayAngle += angleStep;

    }
}



//**************************************************
// Get depth buffer
//**************************************************

float Raycaster::GetDepth(int x) const
{
    if(x < 0 || x >= screenWidth)
        return 999999;


    return depthBuffer[x];
}


}