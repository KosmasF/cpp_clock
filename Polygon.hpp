#pragma once
#include "Object.hpp"
#include "SDL2/SDL.h"
#include "Units.hpp"

class Polygon: public Object
{
public:
    Polygon(Vector2D position, float rotation, Vector2D* points, int num_points, SDL_Color color);
    Polygon(Polygon& other);
    ~Polygon();

    void Draw(SDL_Window* win, Vector2D offset) override;

    Vector2D* RotateAndTranslate();
    Vector2D ReturnPosition() {return position;}
    void SetPosition(Vector2D new_position) {position = new_position;}
    float ReturnRotation() {return rotation;}
    void SetRotation(float new_rotation) {rotation = new_rotation;}

private:
    Vector2D* points;
    int num_points;
    SDL_Color color;

    bool IsPointInPolygon(Vector2D* poly_points, int num, Vector2D point);
    bool IsPolygonColliding(Vector2D* poly1, int num1, Vector2D* poly2, int num2, int* pointOfCollision);
    uint NumPointsColliding(Vector2D* poly1, int num1, Vector2D* poly2, int num2);
};