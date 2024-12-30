#pragma once
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define RADIAN (180.f / M_PIf) //~53
#define NULL_VEC {0,0}
#define TAU (2 * M_PIf)

#define RED {0xff, 0x00, 0x00, 0xff}
#define BLUE {0x00, 0x00, 0xff, 0xff}
#define GREEN {0x00, 0xff, 0x00, 0xff}

float max(float a, float b);
float min(float a, float b);

struct Vector2D
{
    float x;
    float y;

    Vector2D operator*(const Vector2D& other)
    {
        return {x * other.x, y * other.y};
    }

    Vector2D operator/(const Vector2D& other)
    {
        return {x / other.x, y / other.y};
    }

    Vector2D operator*=(const Vector2D& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2D operator+=(const Vector2D& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D operator+(const Vector2D& other)
    {
        return {x + other.x, y + other.y};
    }

    Vector2D operator-=(const Vector2D& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }


    Vector2D operator-(const Vector2D& other)
    {
        return {x - other.x, y - other.y};
    }

    Vector2D operator*(const float scalar)
    {
        return {x * scalar, y * scalar};
    }

    Vector2D operator/(const float scalar)
    {
        return {x / scalar, y / scalar};
    }

    float angle()
    {
        return atan2(y,x);
    }

    float len()
    {
        return sqrt((x*x) + (y*y));
    }

    Vector2D perpendicular() {
        return {-y, x};
    }

    Vector2D parallel()
    {
        return {-x, -y};
    }

    Vector2D rotate(float angle)
    {
        double absolute_value = sqrtf((x * x) + (y * y));
        double point_angle = atan2f(y , x);

        Vector2D point_rotated = {
            (float)(cos(point_angle + angle) * absolute_value),
            (float)(sin(point_angle + angle) * absolute_value)
        };

        return point_rotated;
    }

    operator SDL_Point()
    {
        return {(int)x, (int)y};
    }
};