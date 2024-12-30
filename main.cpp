#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "Loop.hpp"
#include "Circle.hpp"
#include "Units.hpp"
#include "Polygon.hpp"
#include "Map.hpp"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT WINDOW_WIDTH

#define DARK_GREY (SDL_Color){45, 45, 45, 0xff}
#define LIGHT_GREY (SDL_Color){229, 229, 229, 0xff}
#define WHITE (SDL_Color){255, 255, 255, 0xff}
#define LIGHT_BLUE (SDL_Color){225, 239, 240, 0xff}

#define CLOCK_POSITION (Vector2D){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}
#define CLOCK_RADIUS 250   

#define HOUR_MARK_WIDTH 10
#define HOUR_MARK_HEIGHT 60

#define MINUTE_HAND_WIDTH 10
#define MINUTE_HAND_LENGTH (CLOCK_RADIUS * 0.7f)

#define HOUR_HAND_WIDTH 15
#define HOUR_HAND_LENGTH (CLOCK_RADIUS * 0.6f)

#define SECOND_HAND_WIDTH 5
#define SECOND_HAND_LENGTH (CLOCK_RADIUS * 1.05f)
#define SECOND_HAND_OFFSET 55

#define INNER_CIRCLE_RADIUS 15

#define TIMEZONE +2

Vector2D hour_mark[] = {
    {-HOUR_MARK_WIDTH/2, -CLOCK_RADIUS},
    {HOUR_MARK_WIDTH/2, -CLOCK_RADIUS},
    {HOUR_MARK_WIDTH/2, -(CLOCK_RADIUS - HOUR_MARK_HEIGHT)},
    {-HOUR_MARK_WIDTH/2, -(CLOCK_RADIUS - HOUR_MARK_HEIGHT)}
};

Vector2D minute_hand[] = {
    {-MINUTE_HAND_WIDTH/2, 0},
    {MINUTE_HAND_WIDTH/2, 0},
    {MINUTE_HAND_WIDTH/2, -MINUTE_HAND_LENGTH},
    {-MINUTE_HAND_WIDTH/2, -MINUTE_HAND_LENGTH}
};

Vector2D hour_hand[] = {
    {-HOUR_HAND_WIDTH/2, 0},
    {HOUR_HAND_WIDTH/2, 0},
    {HOUR_HAND_WIDTH/2, -HOUR_HAND_LENGTH},
    {-HOUR_HAND_WIDTH/2, -HOUR_HAND_LENGTH}
};

Vector2D second_hand[] = {
    {-SECOND_HAND_WIDTH/2.f, 0 + SECOND_HAND_OFFSET},
    {SECOND_HAND_WIDTH/2.f, 0 + SECOND_HAND_OFFSET},
    {SECOND_HAND_WIDTH/2.f, -(SECOND_HAND_LENGTH - SECOND_HAND_OFFSET)},
    {-SECOND_HAND_WIDTH/2.f, -(SECOND_HAND_LENGTH - SECOND_HAND_OFFSET)}
};

Polygon hour_mark_polygon = Polygon(CLOCK_POSITION, 0, hour_mark, sizeof(hour_mark)/sizeof(Vector2D), DARK_GREY);
Polygon minute_hand_polygon = Polygon(CLOCK_POSITION, 0, minute_hand, sizeof(minute_hand)/sizeof(Vector2D), DARK_GREY);
Polygon hour_hand_polygon = Polygon(CLOCK_POSITION, 0, hour_hand, sizeof(hour_hand)/sizeof(Vector2D), DARK_GREY);
Polygon second_hand_polygon = Polygon(CLOCK_POSITION, 0, second_hand, sizeof(second_hand)/sizeof(Vector2D), RED);

int main()
{
    int ret;
    ret = SDL_Init(SDL_INIT_EVERYTHING);
    if (ret != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Clock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
    if (icon == nullptr)
    {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetWindowIcon(win, icon);
    SDL_FreeSurface(icon);

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
    if (renderer == nullptr)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    while(Loop())
    {
        ret = SDL_SetRenderDrawColor(renderer, LIGHT_BLUE.r, LIGHT_BLUE.g, LIGHT_BLUE.b, LIGHT_BLUE.a);
        ret = SDL_RenderClear(renderer);		
        
        // --------------------UPDATE HANDS--------------------
        time_t current_time = time(NULL); 
        int second = current_time % 60;
        second_hand_polygon.SetRotation(map(second, 0, 60, 0, TAU));

        int minute = (current_time / 60) % 60;
        minute_hand_polygon.SetRotation(map(minute, 0, 60, 0, TAU));

        int hour = (current_time / 60) % (60 * 12);
        hour += TIMEZONE * 60;
        hour_hand_polygon.SetRotation(map(hour, 0, 60 * 12, 0, TAU));


        
        // --------------------DRAW CLOCK--------------------
        DrawCircle(win, CLOCK_POSITION, CLOCK_RADIUS, DARK_GREY);
		DrawCircle(win, CLOCK_POSITION, CLOCK_RADIUS - 30, LIGHT_GREY);
		DrawCircle(win, CLOCK_POSITION, CLOCK_RADIUS - 40, WHITE);

        // --------------------DRAW HOUR MARKS--------------------
        for(int i = 0; i < 12; i++)
        {
            hour_mark_polygon.SetRotation(i * (TAU / 12));
            hour_mark_polygon.Draw(win, NULL_VEC);
        }

        // --------------------DRAW HANDS--------------------
		minute_hand_polygon.Draw(win, NULL_VEC);
        hour_hand_polygon.Draw(win, NULL_VEC);
        second_hand_polygon.Draw(win, NULL_VEC);

        // --------------------DRAW INNER CIRCLE--------------------
        DrawCircle(win, CLOCK_POSITION, INNER_CIRCLE_RADIUS, DARK_GREY);

        SDL_RenderPresent(renderer);
        ret = SDL_UpdateWindowSurface(win);
    }


    return 0;
}