#include "ball.h"

#define GRAVITY_STEP 0.000091

void ball_init(ball_t* ball, float x, float y, uint8_t radius)
{
    ball->x = x;
    ball->y = y;
    ball->radius = radius;
    ball->velocity = 0;
}

void ball_update(ball_t* ball, uint32_t tick)
{
    ball->y += ball->velocity;

    ball->velocity += GRAVITY_STEP;

    if(ball->y < 3)
    {
        ball->y = 5;
        ball->velocity = 0;
    }
    if (ball->y > 58)
    {
        ball->y = 58;
        ball->velocity = 0;
    }

}

void ball_jump(ball_t* ball)
{
    ball->velocity = -0.038;
}