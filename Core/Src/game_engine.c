#include "game_engine.h"
#include "game_render.h"
#include "pipe.h"
#include "ball.h"
#include "stm32g0xx_hal.h"

static ball_t ball;
static pipe_t pipe;

typedef enum{
    START_MENU,
    GAME_MODE,
    GAME_OVER
}game_engine_state;

typedef struct{
    game_engine_state current_state;
}game_engine_t;

static game_engine_t game_engine;

static uint8_t check_for_collision();

void game_engine_init()
{
  game_engine.current_state = START_MENU;
  ball_init(&ball, 30, 30, 3);
  pipe_init(&pipe);
}

void game_engine_step(uint8_t btn_pressed)
{
    switch(game_engine.current_state)
    {
        case START_MENU:
            game_render_start_menu();
            if(btn_pressed)
                game_engine.current_state = GAME_MODE;
            break;
        case GAME_MODE:
            if(btn_pressed)
                ball_jump(&ball);

            ball_update(&ball, HAL_GetTick());
            pipe_update(&pipe);

            game_render_ball(&ball);
            game_render_pipe(&pipe);

            if(check_for_collision())
                game_engine.current_state = GAME_OVER;
            break;
        case GAME_OVER:
            game_render_gameover(pipe.cnt);
            if(btn_pressed)
            {
                ball_init(&ball, 30, 30, 3);
                pipe_init(&pipe);
                game_engine.current_state = GAME_MODE;
            }
            break;
        default:
            game_render_start_menu();
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