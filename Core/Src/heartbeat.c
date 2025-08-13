/**
 * @file heartbeat.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-08-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "heartbeat.h"

void heartbeat_led_initialize(heartbeat_led_t* led,  GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint16_t period)
{
    led->gpio_port = GPIOx;
    led->gpio_pin = GPIO_Pin;
    led->period_ms = period;

    led->last_toggle_tick = 0;

    // active high, initial state OFF
    heartbeat_led_off(led);
}

void heartbeat_led_on(heartbeat_led_t* led)
{
    HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, 1);
    led->state = 1;
}

void heartbeat_led_off(heartbeat_led_t* led)
{
    HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, 0);
    led->state = 0;
}

void heartbeat_led_toggle(heartbeat_led_t* led, uint32_t current_tick)
{
    if(current_tick - led->last_toggle_tick >= led->period_ms)
    {
        led->state = !led->state;
        HAL_GPIO_TogglePin(led->gpio_port, led->gpio_pin);
        led->last_toggle_tick = current_tick;
    }
}
