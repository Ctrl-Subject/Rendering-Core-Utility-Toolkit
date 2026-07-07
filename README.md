# Raycaster


# Documentation
Recorded Tests found on youtube here: https://youtube.com/playlist?list=PLPsrBXBQIJH26BPX7QcmQiE6eikzPqQ4l&amp;si=06rq049dwvZ3mNne

#not sure how helpful will be but this is the code i needed to compile it to a dll
g++ -shared -o Renderer.dll src/Renderer.cpp src/Camera.cpp src/TileMap.cpp src/Raycaster.cpp src/Sprite.cpp src/Texture.cpp -Iinclude -IThirdParty -DRENDERER_EXPORTS -lopengl32 -lfreeglut
