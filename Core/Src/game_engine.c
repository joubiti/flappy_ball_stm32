#include "game_engine.h"
#include "game_render.h"
#include "pipe.h"
#include "ball.h"
#include "stm32g0xx_hal.h"

static ball_t ball;
static pipe_t pipe;


static uint8_t check_for_collision();

void game_engine_init()
{
  ball_init(&ball, 30, 30, 3);
  pipe_init(&pipe);
}

void game_engine_step(uint8_t btn_pressed)
{
    if(btn_pressed)
        ball_jump(&ball);

    ball_update(&ball, HAL_GetTick());
    pipe_update(&pipe);

    game_render_ball(&ball);
    game_render_pipe(&pipe);

    volatile uint8_t status = check_for_collision();
    if(status == 1){
        while(1);
    }
}


static uint8_t check_for_collision()
{
    // get dimensions of the gap
    // y dimensions: (pipe->y_gap, pipe->y_gap + pipe->gap)
    // ball must fit inside these dimensions, taking into account radius?
    if( (pipe.x - 2 < ball.x) && (ball.x < pipe.x))
    {
        if((pipe.y_gap <= ball.y - ball.radius && ball.y + ball.radius <= pipe.y_gap + pipe.gap))
        {
            return 0;
        }
        return 1;
    }
    return 0;
}