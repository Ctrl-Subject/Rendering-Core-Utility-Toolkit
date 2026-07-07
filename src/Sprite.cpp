#include "Sprite.h"

#include <GL/freeglut.h>

#include <algorithm>
#include <cmath>


#define PI 3.1415926535f


namespace RCUT
RCUTRenderer
{


    //**************************************************
    // Remove sprites from render queue
    //**************************************************

    void Sprite
RCUTRenderer::Clear()
    {
        sprites.clear();
    }



    //**************************************************
    // Add sprite
    //**************************************************

    void Sprite
RCUTRenderer::Add(
        const Sprite& sprite
    )
    {
        sprites.push_back(sprite);
    }



    //**************************************************
    // Sort sprites by distance
    //
    // Furthest sprites render first.
    //**************************************************

    static bool SortSprites(
        const Sprite& a,
        const Sprite& b,
        const Camera& camera
    )
    {
        float distA =
            (a.x - camera.GetX()) *
            (a.x - camera.GetX())
            +
            (a.y - camera.GetY()) *
            (a.y - camera.GetY());


        float distB =
            (b.x - camera.GetX()) *
            (b.x - camera.GetX())
            +
            (b.y - camera.GetY()) *
            (b.y - camera.GetY());


        return distA > distB;
    }



    //**************************************************
    // Render sprites
    //**************************************************

    void Sprite
RCUTRenderer::Render(
        const Camera& camera,
        const Raycaster& raycaster,
        int screenWidth,
        int screenHeight
    )
    {

        //**************************************************
        // Sort sprites
        //**************************************************

        std::sort(
            sprites.begin(),
            sprites.end(),

            [&](const Sprite& a, const Sprite& b)
            {
                return SortSprites(
                    a,
                    b,
                    camera
                );
            }
        );



        //**************************************************
        // Draw sprites
        //**************************************************

        for(const Sprite& sprite : sprites)
        {

            float dx = sprite.x - camera.GetX();
            float dy = sprite.y - camera.GetY();


            float distance = sqrt(dx*dx + dy*dy);


            if(distance <= 0.01f)
                continue;



            //**************************************************
            // Find sprite angle
            //**************************************************

            float spriteAngle = atan2(dy,dx);


            float angleDifference =
                spriteAngle -
                camera.GetAngle();



            while(angleDifference > PI)
                angleDifference -= 2 * PI;


            while(angleDifference < -PI)
                angleDifference += 2 * PI;



            if(fabs(angleDifference) > camera.GetFOV()/2)
                continue;



            //**************************************************
            // Convert world position to screen
            //**************************************************

            float screenX =
                (0.5f + angleDifference / camera.GetFOV())
                *
                screenWidth;



            float spriteHeight =
                (sprite.height * screenHeight)
                /
                distance
                *
                sprite.scale;



            float spriteWidth =
                (sprite.width * screenHeight)
                /
                distance
                *
                sprite.scale;



            float startX =
                screenX -
                spriteWidth/2;


            float startY =
                screenHeight/2 -
                spriteHeight/2;



            //**************************************************
            // Bind texture
            //**************************************************

            glEnable(GL_TEXTURE_2D);


            glBindTexture(
                GL_TEXTURE_2D,
                sprite.texture
            );


            glColor3f(
                1,
                1,
                1
            );



            //**************************************************
            // Draw sprite columns
            //
            // Allows walls to hide sprite sections.
            //**************************************************

            for(int x = 0; x < spriteWidth; x++)
            {

                int screenColumn =
                    (int)startX + x;



                if(screenColumn < 0 ||
                screenColumn >= screenWidth)
                    continue;



                float wallDistance =
                    raycaster.GetDepth(
                        screenColumn
                    );



                if(distance > wallDistance)
                    continue;



                float texX =
                    (float)x /
                    spriteWidth;



                glBegin(GL_QUADS);


                    glTexCoord2f(
                        texX,
                        0
                    );

                    glVertex2f(
                        screenColumn,
                        startY
                    );


                    glTexCoord2f(
                        texX + (1.0f/spriteWidth),
                        0
                    );

                    glVertex2f(
                        screenColumn + 1,
                        startY
                    );


                    glTexCoord2f(
                        texX + (1.0f/spriteWidth),
                        1
                    );

                    glVertex2f(
                        screenColumn + 1,
                        startY + spriteHeight
                    );


                    glTexCoord2f(
                        texX,
                        1
                    );

                    glVertex2f(
                        screenColumn,
                        startY + spriteHeight
                    );


                glEnd();

            }


            glDisable(
                GL_TEXTURE_2D
            );

        }

    }


}