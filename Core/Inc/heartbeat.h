#ifndef _HEARTBEAT_H
#define _HEARTBEAT_H

#include "stm32g0xx_hal.h"

/**
 * @brief Structure defining our heartbeat LED object
 * 
 */
typedef struct{
    GPIO_TypeDef* gpio_port;
    uint16_t gpio_pin;
    uint16_t period_ms;
    uint32_t last_toggle_tick;
    uint8_t state;    
}heartbeat_led_t;

/**
 * @brief Initialize the LED object
 * 
 * @param led pointer to the LED object
 * @param GPIOx the GPIO port
 * @param GPIO_Pin the GPIO pin number
 * @param period toggling frequency in milliseconds
 */
void heartbeat_led_initialize(heartbeat_led_t* led,  GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint16_t period);

/**
 * @brief Turn on the heartbeat LED
 * 
 * @param led pointer to the LED object
 */
void heartbeat_led_on(heartbeat_led_t* led);

/**
 * @brief Turn off the heartbeat LED
 * 
 * @param led pointer to the LED object
 */
void heartbeat_led_off(heartbeat_led_t* led);

/**
 * @brief Toggle the heartbeat LED with the configured frequency
 * 
 * @param led pointer to the LED object
 * @param current_tick current tick value in (ms)
 */
void heartbeat_led_toggle(heartbeat_led_t* led, uint32_t current_tick);


#endif