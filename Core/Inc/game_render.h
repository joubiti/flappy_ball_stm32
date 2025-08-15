#ifndef _GAME_RENDER
#define _GAME_RENDER

#include "ball.h"
#include "pipe.h"

/**
 * @brief Render the start menu
 * 
 */
void game_render_start_menu();

/**
 * @brief Render the game over menu and showcase number of pipes crossed
 * 
 * @param pipe_count 
 */
void game_render_gameover(uint32_t pipe_count);

/**
 * @brief Render the ball object
 * 
 * @param ball 
 */
void game_render_ball(ball_t* ball);

/**
 * @brief Render the pipe object
 * 
 * @param pipe 
 */
void game_render_pipe(pipe_t* pipe);


#endif