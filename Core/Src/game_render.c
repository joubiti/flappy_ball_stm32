#include "game_render.h"
#include "ugui.h"


void game_render_ball(ball_t* ball)
{
    UG_FillCircle(ball->x, ball->y, ball->radius, 1);
}

void game_render_pipe(pipe_t* pipe)
{
    // UG_FillFrame(125, 0, 125-2, 63, 1);
    UG_FillFrame(pipe->x, 0, (pipe->x - 2), pipe->y_gap, 1);
    UG_FillFrame(pipe->x, pipe->y_gap + pipe->gap, (pipe->x - 2), 63, 1);
    // UG_FillFrame(pipe->x, pi)
}
