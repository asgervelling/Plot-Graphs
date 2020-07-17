#ifndef ANIMATION
#define ANIMATION
#include "structs.h"

double coord_sys_y(State *state, double y);
int coord_sys_x(State *state, int x);
void zoom_in(State *state);
void zoom_out(State *state);
void draw_coord_sys(State *state);
void draw_point_test(State *state);
int draw_linear_equation(State *state, double a, double b, int filled);
void draw_exponential_equation(State *state, double a, double exponent, double b);

#endif