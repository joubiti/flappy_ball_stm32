#ifndef _BIRD_H
#define _BIRD_H

#include "stdint.h"

/**
 * @brief Ball objects
 * 
 */
typedef struct{
    float x;
    float y;
    float velocity;
    uint8_t radius;
    uint32_t last_tick;
}ball_t;

/**
 * @brief Initialize the ball object with x,y coordinates and radius
 * 
 * @param ball 
 * @param x 
 * @param y 
 * @param radius 
 */
void ball_init(ball_t* ball, float x, float y, uint8_t radius);

/**
 * @brief Update the ball dynamics (gravity, velocity, coordiantes)
 * 
 * @param ball 
 * @param tick 
 */
void ball_update(ball_t* ball, uint32_t tick);

/**
 * @brief Apply velocity boost upwards to the ball
 * 
 * @param ball 
 */
void ball_jump(ball_t* ball);


#endif