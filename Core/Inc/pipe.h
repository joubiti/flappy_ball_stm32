#ifndef _PIPE_H
#define _PIPE_H

#include "stdint.h"

typedef struct{
    float x;
    float y;
    uint8_t gap;
    uint8_t y_gap;
    uint8_t width;
    float velocity;
}pipe_t;

void pipe_init(pipe_t* pipe);
void pipe_update(pipe_t* pipe);


#endif