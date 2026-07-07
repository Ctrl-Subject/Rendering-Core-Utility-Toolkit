#include "Camera.h"

#include <cmath>

#define PI 3.1415926535f

namespace RCUT
RCUTRenderer
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
}