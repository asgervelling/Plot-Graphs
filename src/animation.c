#include "animation.h"

#define DISPLAY_HEIGHT 800
#define DISPLAY_WIDTH 600

double coord_sys(double y)
{
    // Returns value of y in a normal coordinate system.
    // x is the same
    double new_y = DISPLAY_HEIGHT - y;
    printf("cy = %.1f, y = %.1f\n", new_y, y);
    return new_y;
}

void draw_point_test(GameState *game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    for (int i = 0; i < 400; ++i)
    {
        SDL_RenderDrawPoint(game->renderer, i, i);
    }
}

int draw_linear_equation(GameState *game, double a, double b)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    for (int x = 0; x < game->settings.display_width; ++x)
    {
        double fx = coord_sys(a*x + b);
        printf("x = %d\n\n", x);
        SDL_RenderDrawPoint(game->renderer, x, fx);
    }

    return 0;
}

