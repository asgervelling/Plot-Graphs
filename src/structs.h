#ifndef STRUCTS
#define STRUCTS
#include <SDL2/SDL.h>

typedef struct
{
    int min_x, max_x;
    int min_y, max_y;
    float zoom_x, zoom_y;
} Coordinate_System;

typedef struct
{
    int display_width, display_height;
} Settings;

typedef struct
{
    int x, y, w, h;
} Actor;

typedef struct
{
    int current_frame;
    int current_animation;
} Animation;

enum animations
{
    linear
};

typedef struct
{
    int screen_state;
    Actor animated_rect;
    Settings settings;
    Coordinate_System coord_sys;
    Animation anim;
    SDL_Renderer *renderer;
} State;
#endif