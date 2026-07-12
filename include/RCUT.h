#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <GL/freeglut.h>

namespace RCUTRenderer
{
    class Raycaster
    {
        private:
            float* depthBuffer;
            int screenWidth;
        public:
            Raycaster();
            ~Raycaster();

            void Initialize(int width);

            void Render(const TileMap& map, const Camera& camera, int screenHeight);

            float GetDepth(int x) const;
    };

    class Renderer
        {
        public:
            static bool Initialize(int width, int height);

            static void Shutdown();

            static void BeginFrame();

            static void EndFrame();

            static void RenderMap(
                int* tiles,
                int width,
                int height,
                int tileSize,
                float playerX,
                float playerY,
                float playerAngle
            );
    };

    struct Sprite
    {
        TextureID texture;

        float x;
        float y;
        float width;
        float height;
        float scale;

        Sprite()
        {
            texture = 0;
            x = 0;
            y = 0;
            width = 64;
            height = 64;
            scale = 1.0f;
        }
    };

    class SpriteRenderer
    {
        private:
            std::vector<Sprite> sprites;
        public:
            void Clear();
            void Add(const Sprite& sprite);
            void Render(const Camera& camera, const Raycaster& raycaster, int screenWidth, int screenHeight);
    };

    using TextureID = unsigned int;
    class TextureManager
    {
        public:

            static TextureID Load(const char* filename );
            static TextureID FromRaw(TextureID existing);

            static void Destroy(TextureID id);
            static void Bind(TextureID id);
    };

    class TileMap
    {
        public:
            int width;
            int height;
            int tileSize;

            std::vector<int> tiles;

        public:
            TileMap();
            TileMap(int width, int height, int tileSize);

            int GetTile(int x, int y) const;
            void SetTile(int x, int y, int value);
    };

    class Camera
    {
        private:
            float x;
            float y;
            float angle;
            float fov;

        public:
            Camera();
            void SetPosition(float x, float y);
            float GetX() const;
            float GetY() const;

            void SetAngle(float angle);
            void Rotate(float amount);
            float GetAngle() const;
            void SetFOV(float value);
            float GetFOV() const;
    };
}
