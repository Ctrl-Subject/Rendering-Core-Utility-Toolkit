#include "TileMap.h"


namespace RCUTRenderer
{

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