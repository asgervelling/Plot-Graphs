#ifndef ANIMATION
#define ANIMATION
#include "structs.h"

double coord_sys_y(double y);
int coord_sys_x(int x);
void draw_coord_sys(GameState *game);
void draw_point_test(GameState *game);
int draw_linear_equation(GameState *game, double a, double b, int filled);

#endif