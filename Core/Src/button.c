#include "button.h"

/**
 * @brief Internal static function to read GPIO state using HAL
 * 
 * @param btn pointer to the user button object
 * @return 1 if button is pressed, 0 otherwise
 */
static inline uint8_t button_read_state(button_t* btn);

void button_initialize(button_t* btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    btn->gpio_port = GPIOx;
    btn->gpio_pin = GPIO_Pin;
    btn->debounce_period_ms = 50;
    btn->last_state = 0;
    btn->last_read_tick = 0;
}

static inline uint8_t button_read_state(button_t* btn)
{
    return !HAL_GPIO_ReadPin(btn->gpio_port, btn->gpio_pin);
}

uint8_t is_button_pressed(button_t* btn, uint32_t current_tick)
{
    uint8_t raw_state = button_read_state(btn);
    uint8_t pressed = 0;
    if(raw_state && !btn->last_state)
    {
        if(current_tick - btn->last_read_tick >= btn->debounce_period_ms)
        {
            pressed = 1;
            btn->last_read_tick = current_tick;
        }
    }
    btn->last_state = raw_state;
    return pressed;
}