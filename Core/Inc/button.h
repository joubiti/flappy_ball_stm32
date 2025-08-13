#ifndef _BUTTON_H
#define _BUTTON_H

#include "stm32g0xx_hal.h"

/**
 * @brief Structure for the user button object
 * 
 */
typedef struct{
    GPIO_TypeDef* gpio_port;
    uint16_t gpio_pin;
    uint16_t debounce_period_ms;
    uint32_t last_read_tick;
    uint8_t last_state;
}button_t;

/**
 * @brief Initialize the user button object
 * 
 * @param btn pointer to the user button object
 * @param GPIOx port number
 * @param GPIO_Pin pin number
 */
void button_initialize(button_t* btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Returns whether the button is pressed or not, taking into account debounce period
 * 
 * @param btn pointer to the user button object
 * @param current_tick current tick in (ms)
 * @return 1 if button is pressed, 0 otherwise
 */
uint8_t is_button_pressed(button_t* btn, uint32_t current_tick);



#endif