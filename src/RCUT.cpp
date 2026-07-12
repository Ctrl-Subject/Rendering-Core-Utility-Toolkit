#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "RCUT.h"

#define PI 3.1415926535f

namespace RCUTRenderer
{

    //**************************************************
    // Constructor
    //**************************************************

    Camera::Camera()
    {
        x = 0;
        y = 0;
        angle = 0;
        fov = PI / 3.0f;
    }

    //**************************************************
    // Position
    //**************************************************

    void Camera::SetPosition(float newX,float newY)
    {
        x = newX;

        y = newY;
    }

    float Camera::GetX() const
    {
        return x;
    }

    float Camera::GetY() const
    {
        return y;
    }

    //**************************************************
    // Rotation
    //**************************************************

    void Camera::SetAngle(float value)
    {
        angle = value;

        while(angle < 0)
            angle += 2 * PI;

        while(angle > 2 * PI)
            angle -= 2 * PI;
    }

    void Camera::Rotate(float amount)
    {
        angle += amount;

        while(angle < 0)
            angle += 2 * PI;

        while(angle > 2 * PI)
            angle -= 2 * PI;
    }

    float Camera::GetAngle() const
    {
        return angle;
    }

    //**************************************************
    // FOV
    //**************************************************

    void Camera::SetFOV(
        float value
    )
    {
        fov = value;
    }

    float Camera::GetFOV() const
    {
        return fov;
    }

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


    //**************************************************
    // Remove sprites from render queue
    //**************************************************

    void SpriteRenderer::Clear()
    {
        sprites.clear();
    }

    //**************************************************
    // Add sprite
    //**************************************************

    void SpriteRenderer::Add(
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

    void SpriteRenderer::Render(
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


    //**************************************************
    // Load texture
    //
    // Loads an image and creates an OpenGL texture.
    //
    // NOTE:
    // Image decoding is not implemented yet.
    // This will be replaced with stb_image later.
    //
    // Returns:
    // 0 = failed
    // >0 = texture ID
    //**************************************************

    TextureID TextureManager::Load(
        const char* filename
    )
    {
        FILE* file = fopen(
            filename,
            "rb"
        );

        if(!file)
        {
            printf(
                "Failed to open texture: %s\n",
                filename
            );

            return 0;
        }

        fclose(file);

        //**************************************************
        // Create OpenGL texture
        //**************************************************

        TextureID texture = 0;

        glGenTextures(
            1,
            &texture
        );

        glBindTexture(
            GL_TEXTURE_2D,
            texture
        );

        //**************************************************
        // Texture settings
        //
        // NEAREST keeps the pixelated look.
        // Good for Pac-Man style graphics.
        //**************************************************

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_NEAREST
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_NEAREST
        );

        //**************************************************
        // Texture wrapping
        //**************************************************

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_CLAMP
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_CLAMP
        );

        return texture;
    }

    //**************************************************
    // Destroy texture
    //
    // Frees GPU memory.
    //**************************************************

    void TextureManager::Destroy(
        TextureID id
    )
    {
        if(id == 0)
            return;

        glDeleteTextures(
            1,
            &id
        );
    }

    //**************************************************
    // Bind texture
    //
    // Makes a texture active for rendering.
    //**************************************************

    void TextureManager::Bind(
        TextureID id
    )
    {
        glBindTexture(
            GL_TEXTURE_2D,
            id
        );
    }

//**************************************************
    // Empty map
    //**************************************************

    TileMap::TileMap()
    {

        width = 0;

        height = 0;

        tileSize = 64;
    }

    //**************************************************
    // Create map
    //**************************************************

    TileMap::TileMap(int w, int h, int size)
    {
        width = w;

        height = h;

        tileSize = size;

        tiles.resize(width * height);
    }

    //**************************************************
    // Get tile
    //**************************************************

    int TileMap::GetTile(int x,int y) const
    {
        if(x < 0 || y < 0 || x >= width || y >= height)
            return 1;

        return tiles[y * width + x];
    }

    //**************************************************
    // Set tile
    //**************************************************

    void TileMap::SetTile(int x, int y,int value)
    {
        if(x < 0 || y < 0 || x >= width || y >= height)
            return;

        tiles[y * width + x] = value;
    }
}
