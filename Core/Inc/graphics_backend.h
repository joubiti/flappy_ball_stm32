#ifndef _GRAPHICS_BACKEND
#define _GRAPHICS_BACKEND


#include "ugui.h"
#include "oled.h"

/**
 * @brief Graphics backend structure which takes reference to the graphics library object
 * 
 */
typedef struct{
    UG_GUI* gui;
    oled_screen_t* oled;
    uint32_t last_tick;
}graphics_backend_t;

/**
 * @brief Initialize the graphics backend and the µGUI library
 * 
 * @param backend 
 * @param oled 
 */
void graphics_backend_init(graphics_backend_t* backend, oled_screen_t* oled);

/**
 * @brief Update OLED with framebuffer contents (50 Hz)
 * 
 * @param backend 
 * @param current_tick 
 */
void graphics_backend_update(graphics_backend_t* backend, uint32_t current_tick);


#endif