#include "pipe.h"
#include "stdlib.h"

#define MIN_GAP 20
#define MAX_GAP 40

static inline uint8_t rand_range(uint8_t min, uint8_t max)
{
    return (uint8_t)(min + (rand() % (max - min + 1)));
}

void pipe_init(pipe_t* pipe)
{
    pipe->x = 125;
    pipe->y = 0;
    pipe->gap = 25; // initial gap, will be randomized after each update
    pipe->y_gap = 8;
    pipe->width = 2;
    pipe->cnt = 0;
    pipe->velocity = 0.0556f;
}

void pipe_update(pipe_t* pipe)
{
    pipe->x -= pipe->velocity;
    if(pipe->x < 4) // if pipe reaches end of road, respawn with new gap
    {
        pipe->x = 125;
        pipe->gap = rand_range(MIN_GAP, MAX_GAP);
        pipe->y_gap = rand_range(10, 20);
        pipe->cnt++;
        // pipe->velocity = ; speed control eventually
    }
}