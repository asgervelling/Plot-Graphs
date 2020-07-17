#include "animation.h"

#define DISPLAY_HEIGHT 600
#define DISPLAY_WIDTH 800

double coord_sys_y(State *state, double y)
{
    // Returns value of y in a normal cartesian coordinate system.
    double new_y = state->settings.display_height / 2 - y;
    return new_y;
}

int coord_sys_x(State *state, int x)
{
    // Returns value of y in a normal cartesian coordinate system.
    int y_axis_x_value = state->settings.display_width / 2;
    int new_x = y_axis_x_value + x;
    return new_x;
}

void draw_coord_sys(State *state)
{
    int x_axis_y_value = state->settings.display_height / 2;
    int y_axis_x_value = state->settings.display_width / 2;

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    // Draw x axis
    for (int x = 0; x < DISPLAY_WIDTH; ++x)
    {
        SDL_RenderDrawPoint(state->renderer, x, x_axis_y_value);
    }
    // Draw y axis
    for (int y = 0; y < DISPLAY_HEIGHT; ++y)
    {
        SDL_RenderDrawPoint(state->renderer, y_axis_x_value, y);
    }
}

void draw_point_test(State *state)
{
    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, 255);
    for (int i = 0; i < 400; ++i)
    {
        SDL_RenderDrawPoint(state->renderer, i, i);
    }
}

int draw_linear_equation(State *state, double a, double b, int filled)
{
    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, 255);
    for (int x = state->coord_sys.min_x; x < state->coord_sys.max_x; ++x)
    {
        double fx = a*x + b;
        
        SDL_RenderDrawPoint(state->renderer, coord_sys_x(state, x), coord_sys_y(state, fx));
        printf("f(%d) = %.1f\n", coord_sys_x(state, x), coord_sys_y(state, fx));

        if (filled == 1)
        {
            // Fill area under graph (optional)
            for (int y = 0; y < fx; ++y)
            {
                SDL_RenderDrawPoint(state->renderer, x, y);
            }
        }
    }

    return 0;
}

void draw_exponential_equation(State *state, double a, double exponent, double b)
{
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 255, 255);

    // Testing
    int x0;
    double y0;
    int x1;
    double y1;

    for (int x = state->coord_sys.min_x; x < state->coord_sys.max_x; ++x)
    {
        x0 = x1;
        y0 = y1;
        // Find f(x) = a*x² + b
        double fx = a*(pow((x * state->coord_sys.zoom_x), exponent) + b);
        x1 = x;
        y1 = fx;

        SDL_RenderDrawLine(state->renderer,
                           coord_sys_x(state, x0),
                           coord_sys_y(state, (int)y0),
                           coord_sys_x(state, x1),
                           coord_sys_y(state, (int)y1));
        // SDL_RenderDrawPoint(state->renderer, coord_sys_x(state, x), coord_sys_y(state, fx));
    }
}


void zoom_in(State *state)
{
    // Zoom in by decreasing zoom_x, but do not go below 0
    float quarter = state->coord_sys.zoom_x / 4;
    state->coord_sys.zoom_x -= quarter;
    printf("zoom in\n");
}

void zoom_out(State *state)
{
    // Zoom out by increasing zoom_x
    float quarter = state->coord_sys.zoom_x / 4;
    state->coord_sys.zoom_x += quarter;
    printf("zoom out\n");
}