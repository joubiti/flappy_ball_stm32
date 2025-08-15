#include "game_render.h"
#include "ugui.h"
#include "string.h"
#include "stdio.h"

void game_render_ball(ball_t* ball)
{
    UG_FillCircle(ball->x, ball->y, ball->radius, 1);
}

void game_render_pipe(pipe_t* pipe)
{
    UG_FillFrame(pipe->x, 0, (pipe->x - 2), pipe->y_gap, 1);
    UG_FillFrame(pipe->x, pipe->y_gap + pipe->gap, (pipe->x - 2), 63, 1);
}

void game_render_start_menu()
{
    UG_SetBackcolor(0);
    UG_SetForecolor(1);
    UG_PutString(10, 25, "Press X to start");
}

void game_render_gameover(uint32_t pipe_count)
{
    UG_SetBackcolor(0);
    UG_SetForecolor(1);

    UG_PutString(0, 20, "Oops! X to restart");
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Score: %ld", pipe_count);
    UG_PutString(0, 40, buffer);
}
