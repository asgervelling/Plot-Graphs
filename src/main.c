#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>

#include "animation.h"

void load_game(GameState *game)
{
    // Init settings
    game->settings.display_width = 800;
    game->settings.display_height = 600;

    game->animated_rect.x = 200;
    game->animated_rect.y = 200;
    game->animated_rect.w = 40;
    game->animated_rect.h = 40;

    // Coordinate system range
    game->coord_sys.min_x = -(game->settings.display_width / 2);
    game->coord_sys.max_x = (game->settings.display_width / 2);
    game->coord_sys.min_y = -(game->settings.display_height / 2);
    game->coord_sys.max_y = (game->settings.display_height / 2);
    return;
}

int listen_for_events(SDL_Window *window, GameState *game, float dt)
{
    SDL_Event event;
    int done = 0;

    // Event loop
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            // Window events
            case(SDL_WINDOWEVENT_CLOSE):
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
            break;

            // Keyboard events
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        done = 1;
                    }
                }
            }
            break;

            // Mouse events
            case SDL_MOUSEBUTTONDOWN:
            {
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                    {
                        done = 0;                                  
                    }
                }
            }
            break;

            // Quit event
            case SDL_QUIT:
            {
                done = 1;
            }
            break;
        }
    }
    /*
    // Keyboard states:
    // What happens when you hold down a button.

    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    if(key_state[SDL_SCANCODE_LEFT])                    // left
    {
        left_key(game, dt);

    }
    if(key_state[SDL_SCANCODE_RIGHT])                   // right
    {
        right_key(game, dt);
    }

    if(key_state[SDL_SCANCODE_DOWN])                   // right
    {
        down_key(game, dt);
    }
    */

    return done;
}

void render(SDL_Renderer *renderer, GameState *game)
{
    /*
    Render stuff here. Some useful functions include:

    SDL_SetRenderDrawColor(SDL_Renderer * renderer,
                                           Uint8 r, Uint8 g, Uint8 b,
                                           Uint8 a):
        Sets your current draw color (imagine a paint brush you have dipped in a color)
    
    SDL_RenderFillRect(SDL_Renderer * renderer, const SDL_Rect * rect)):
        Fills an SDL_Rect with whatever color you have chosen.
    
    SDL_RenderClear(SDL_Renderer * renderer):
        Clears the screen (sets the screen color to the chosen color)-
        Use this every frame.

    and most importantly:

    SDL_RenderPresent(SDL_Renderer * renderer):
        Renders everything and "puts it on the screen".
        Use every frame at the end of this function.
    */

    // Background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    /*
     // Animated rect
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect anim_rect = {game->animated_rect.x,
                          game->animated_rect.y,
                          game->animated_rect.w,
                          game->animated_rect.h};
    SDL_RenderFillRect(renderer, &anim_rect);
    */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    draw_coord_sys(game);
    draw_linear_equation(game, 2, 32, 0);

    SDL_RenderPresent(renderer);
}

void process(GameState *game, float dt)
{
    return;
}

int main(int argc, char* argv[])
{
    void load_game(GameState *game);
    int listen_for_events(SDL_Window *window, GameState *game, float dt);
    void render(SDL_Renderer *renderer, GameState *game);
    void process(GameState *game, float dt);

    // Declare a game state that will be used a lot
    GameState game_state;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Load
    load_game(&game_state);
    
    // Init SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create window
    window = SDL_CreateWindow("Animation Program",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              game_state.settings.display_width,
                              game_state.settings.display_height,
                              0);
    
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    game_state.renderer = renderer;

    // Init SDL_ttf (for text fonts)
    TTF_Init();

    
    
    /*********
    EVENT LOOP
    *********/
    int done = 0;

    // Time stuff
    Uint32 t1 = SDL_GetTicks();
    float frame_duration = 16.666; // 60th of a second
    while(!done)
    {
        // Delta time
        Uint32 t2 = SDL_GetTicks();
        float dt = (t2 - t1) / 1000.0f;

        if (listen_for_events(window, &game_state, dt) == 1)
        {
            done = 1;
        }
        render(renderer, &game_state);
        process(&game_state, dt);

        // Delta time
        t1 = t2;
        SDL_Delay(floor(frame_duration - dt));
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
