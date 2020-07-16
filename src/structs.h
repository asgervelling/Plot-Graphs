#ifndef STRUCTS
#define STRUCTS
#include <SDL2/SDL.h>

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
    Animation anim;
    SDL_Renderer *renderer;
} GameState;
#endif