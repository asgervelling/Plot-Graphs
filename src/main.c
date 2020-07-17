#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>

#include "animation.h"

void load_game(State *state)
{
    // Init settings
    state->settings.display_width = 800;
    state->settings.display_height = 600;

    state->animated_rect.x = 200;
    state->animated_rect.y = 200;
    state->animated_rect.w = 40;
    state->animated_rect.h = 40;

    // Coordinate system range
    state->coord_sys.min_x = -(state->settings.display_width / 2);
    state->coord_sys.max_x = (state->settings.display_width / 2);
    state->coord_sys.min_y = -(state->settings.display_height / 2);
    state->coord_sys.max_y = (state->settings.display_height / 2);
    state->coord_sys.zoom_x = 1;
    return;
}

int listen_for_events(SDL_Window *window, State *state, float dt)
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
                    break;
                    
                    case SDLK_UP:
                    {
                        // Zoom in (x)
                        zoom_in(state);
                    }
                    break;

                    case SDLK_DOWN:
                    {
                        // Zoom out (x)
                        zoom_out(state);
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

    return done;
}

void render(SDL_Renderer *renderer, State *state)
{
    // Background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Coordinate system
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    draw_coord_sys(state);

    // Functions
    // draw_linear_equation(state, 2, 32, 0);
    draw_exponential_equation(state, 1, 2, 0); // f(x) = x²

    SDL_RenderPresent(renderer);
}

void process(State *state, float dt)
{
    return;
}

int main(int argc, char* argv[])
{
    void load_game(State *state);
    int listen_for_events(SDL_Window *window, State *state, float dt);
    void render(SDL_Renderer *renderer, State *state);
    void process(State *state, float dt);

    // Declare a state state that will be used a lot
    State game_state;

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
