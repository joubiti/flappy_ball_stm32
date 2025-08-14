#ifndef _BIRD_H
#define _BIRD_H

#include "stdint.h"

typedef struct{
    float x;
    float y;
    float velocity;
    uint8_t radius;
    uint32_t last_tick;
}ball_t;

void ball_init(ball_t* ball, float x, float y, uint8_t radius);
void ball_update(ball_t* ball, uint32_t tick);
void ball_jump(ball_t* ball);


#endif