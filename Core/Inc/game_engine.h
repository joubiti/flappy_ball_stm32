#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include "stdint.h"

/**
 * @brief Initialize game engine (instantiate pipe, ball object with their physical properties)
 * 
 */
void game_engine_init();

/**
 * @brief Process game input and dynamics
 * 
 */
void game_engine_step(uint8_t btn_pressed);

#endif