#include "Polygon.hpp"

Polygon::Polygon(Vector2D position, float rotation, Vector2D* points, int num_points, SDL_Color color)
: Object(position, rotation)
{
    this->num_points = num_points;
    this->points = (Vector2D*)malloc(num_points * sizeof(Vector2D));
    memcpy(this->points, points, num_points * sizeof(Vector2D));
    this->color = color;
}

Polygon::Polygon(Polygon &other)
: Object(other)
{
    memcpy((void*)(((Object*)this) + 1), (void*)(((Object*)&other) + 1), sizeof(Polygon) - sizeof(Object));
    this->points = (Vector2D*)malloc(num_points * sizeof(Vector2D));
    memcpy(this->points, other.points, num_points * sizeof(Vector2D));
}

Polygon::~Polygon()
{
    free(points);
}

void Polygon::Draw(SDL_Window *win, Vector2D offset)
{
    SDL_Renderer* renderer = SDL_GetRenderer(win);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);


    Vector2D* points_translated = RotateAndTranslate();

    float max_x, max_y, min_x, min_y;
    max_x = max_y = 0;
    min_y = min_x = INFINITY;
    for(int i = 0; i < num_points; i++)
    {
        if(points_translated[i].x > max_x)
            max_x = points_translated[i].x;

        if(points_translated[i].x < min_x)
            min_x = points_translated[i].x;

        if(points_translated[i].y > max_y)
            max_y = points_translated[i].y;

        if(points_translated[i].y < min_y)
            min_y = points_translated[i].y;
    }
    for(int x = min_x; x < max_x; x++)
    {
        for(int y = min_y; y < max_y; y++)
        {                    
            if(IsPointInPolygon(points_translated, num_points, {(float)x, (float)y}))
            {

                SDL_RenderDrawPoint(renderer, x + offset.x, y + offset.y);
            }
        }
    }

    free(points_translated);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderDrawPoint(renderer, CenterOfRotation.x + position.x + offset.x, CenterOfRotation.y + position.y + offset.y);

    //rotation+=0.001f;
}

bool Polygon::IsPointInPolygon(Vector2D* poly_points, int num, Vector2D point)
{
    int intersections = 0;

    for(int i = 0; i < num - 1; i++)
    {
        bool p0 = poly_points[i].y < point.y;
        bool p1 = poly_points[i + 1].y < point.y;

        bool passing = p0 ^ p1;

        if(passing)
        {
            float tan_angle = (poly_points[i].y - poly_points[i + 1].y) / (poly_points[i].x - poly_points[i + 1].x);
            float rel_intersection_x = (point.y - poly_points[i].y) / tan_angle;
            float intersection_x = poly_points[i].x + rel_intersection_x;

            if(intersection_x > point.x)
                intersections++;
        }
    }

    {
        bool p0 = poly_points[num - 1].y < point.y;
        bool p1 = poly_points[0].y < point.y;

        bool passing = p0 ^ p1;

        if(passing)
        {
            float tan_angle = (poly_points[num - 1].y - poly_points[0].y) / (poly_points[num - 1].x - poly_points[0].x);
            float rel_intersection_x = (point.y - poly_points[num - 1].y) / tan_angle;
            float intersection_x = poly_points[num - 1].x + rel_intersection_x;

            if(intersection_x > point.x)
                intersections++;
        }
    }

    return !(intersections % 2 == 0);
}

bool Polygon::IsPolygonColliding(Vector2D *poly1, int num1, Vector2D *poly2, int num2, int *pointOfCollison)
{
    for(int i = 0; i < num1; i++)
    {
        if(IsPointInPolygon(poly2, num2, poly1[i]))
        {
            *pointOfCollison = i;
            return true;
        }
    }

    return false;
}

uint Polygon::NumPointsColliding(Vector2D* poly1, int num1, Vector2D *poly2, int num2)
{
    uint num = 0;
    for(int i = 0; i < num1; i++)
    {
        if(IsPointInPolygon(poly2, num2, poly1[i]))
        {
            num++;
        }
    }

    return num;
}


Vector2D *Polygon::RotateAndTranslate()
{
    //Rotate
    Vector2D* points_rotated = (Vector2D*)malloc(num_points * sizeof(Vector2D));
    //Make relative to CM
    for(int i = 0; i < num_points; i++)
    {
        Vector2D rel_pos = points[i] - CenterOfRotation;

        double absolute_value = sqrt((rel_pos.x * rel_pos.x) + (rel_pos.y * rel_pos.y));
        double point_angle = atan2(rel_pos.y , rel_pos.x);

        points_rotated[i] = {
            (float)(cos(point_angle + rotation) * absolute_value),
            (float)(sin(point_angle + rotation) * absolute_value)
        };
    }
    
    //Translate to position
    Vector2D* points_translated = (Vector2D*)malloc(num_points * sizeof(Vector2D));
    for(int i = 0; i < num_points; i++)
    {
        points_translated[i] = points_rotated[i] + position + CenterOfRotation;
    }

    free(points_rotated);
    return points_translated;
}