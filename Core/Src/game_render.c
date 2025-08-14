#include "game_render.h"
#include "ugui.h"

void game_render_ball(ball_t* ball)
{
    UG_FillCircle(ball->x, ball->y, ball->radius, 1);
}