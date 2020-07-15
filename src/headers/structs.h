#include <SDL2/SDL.h>

typedef struct
{
    int display_width, display_height;
} Settings;

typedef struct
{
    int screen_state;
    Settings settings;
    SDL_Renderer *renderer;
} GameState;
