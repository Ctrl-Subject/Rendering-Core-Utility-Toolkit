#pragma once

#include "RendererAPI.h"
#include <vector>

namespace  RCUTRenderer
{

    class Renderer_API TileMap
    {

    public:

        int width;

        int height;

        int tileSize;



        std::vector<int> tiles;



    public:


        TileMap();


        TileMap(
            int width,
            int height,
            int tileSize
        );



        int GetTile(
            int x,
            int y
        ) const;



        void SetTile(
            int x,
            int y,
            int value
        );

    };

}