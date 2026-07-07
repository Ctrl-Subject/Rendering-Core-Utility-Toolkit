#pragma once

#include "
RCUTRendererAPI.h"

namespace 
RCUTRenderer
{
    class 
RCUTRenderer_API Camera
    {
    private:

        float x;
        float y;

        float angle;

        float fov;

    public:

        Camera();

        //**************************************************
        // Position
        //**************************************************

        void SetPosition(
            float x,
            float y
        );

        float GetX() const;

        float GetY() const;

        //**************************************************
        // Rotation
        //**************************************************

        void SetAngle(
            float angle
        );


        void Rotate(
            float amount
        );

        float GetAngle() const;

        //**************************************************
        // Field of view
        //**************************************************

        void SetFOV(
            float value
        );

        float GetFOV() const;
    };
}