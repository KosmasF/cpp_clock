#include "Circle.hpp"

void DrawCircle(SDL_Window *win, SDL_Point position, int radius, SDL_Color color)
{
    int ret;
    SDL_Renderer *renderer = SDL_GetRenderer(win);
    ret = SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if(ret != 0)
    {
        printf("SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        return;
    }

    for (int x = -radius; x < radius; x++)
    {
        for (int y = -radius; y < radius; y++)
        {
            if(sqrt(pow(x, 2) + pow(y, 2)) <= radius)
            {
                ret = SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
            }
        }
    }
}