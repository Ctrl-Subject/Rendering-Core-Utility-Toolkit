#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"

#include <GL/freeglut.h>
#include <cstdio>


namespace RCUT
RCUTRenderer
{



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


}