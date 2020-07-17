#include "animation.h"

#define DISPLAY_HEIGHT 600
#define DISPLAY_WIDTH 800

double coord_sys_y(double y)
{
    // Returns value of y in a normal cartesian coordinate system.
    double new_y = DISPLAY_HEIGHT / 2 - y;
    return new_y;
}

int coord_sys_x(int x)
{
    // Returns value of y in a normal cartesian coordinate system.
    int y_axis_x_value = DISPLAY_WIDTH / 2;
    int new_x = y_axis_x_value + x;
    printf("x = %d\n", x);
    /*
    if (x >= y_axis_x_value)
    {
        new_x = y_axis_x_value + x;
    }
    else
    {
        new_x = y_axis_x_value - x;
    }
    */
    printf("new_x = %d\n", new_x);
    
    return new_x;
}

void draw_coord_sys(GameState *game)
{
    int x_axis_y_value = game->settings.display_height / 2;
    int y_axis_x_value = game->settings.display_width / 2;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    // Draw x axis
    for (int x = 0; x < DISPLAY_WIDTH; ++x)
    {
        SDL_RenderDrawPoint(game->renderer, x, x_axis_y_value);
    }
    // Draw y axis
    for (int y = 0; y < DISPLAY_HEIGHT; ++y)
    {
        SDL_RenderDrawPoint(game->renderer, y_axis_x_value, y);
    }
}

void draw_point_test(GameState *game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    for (int i = 0; i < 400; ++i)
    {
        SDL_RenderDrawPoint(game->renderer, i, i);
    }
}

int draw_linear_equation(GameState *game, double a, double b, int filled)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    for (int x = game->coord_sys.min_x; x < game->coord_sys.max_y; ++x)
    {
        double fx = a*x + b;
        
        SDL_RenderDrawPoint(game->renderer, coord_sys_x(x), coord_sys_y(fx));
        printf("f(%d) = %.1f\n", coord_sys_x(x), coord_sys_y(fx));

        if (filled == 1)
        {
            // Fill area under graph (optional)
            for (int y = 0; y < fx; ++y)
            {
                SDL_RenderDrawPoint(game->renderer, x, y);
            }
        }
    }

    return 0;
}

