#pragma once
#include "Units.hpp"
#include <SDL2/SDL.h>

class Object
{
public:
    Object(Vector2D position, float rotation);
    Object(Object& other);
    ~Object();

    virtual void Draw(SDL_Window*, Vector2D) {}

protected:
    Vector2D position;
    Vector2D CenterOfRotation = {0, 0};

    float rotation;
};