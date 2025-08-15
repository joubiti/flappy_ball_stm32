#ifndef _PIPE_H
#define _PIPE_H

#include "stdint.h"

/**
 * @brief Pipe object
 * 
 */
typedef struct{
    float x;
    float y;
    uint8_t gap;
    uint8_t y_gap;
    uint8_t width;
    uint32_t cnt; // to track number of pipes crossed
    float velocity;
}pipe_t;

/**
 * @brief Initialize pipe object with fixed x,y coordiantes and initial gap width
 * 
 * @param pipe 
 */
void pipe_init(pipe_t* pipe);

/**
 * @brief Update pipe dynamics (mainly velocity and tracking the number of crossings)
 * 
 * @param pipe 
 */
void pipe_update(pipe_t* pipe);


#endif