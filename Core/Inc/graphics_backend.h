#ifndef _GRAPHICS_BACKEND
#define _GRAPHICS_BACKEND


#include "ugui.h"
#include "oled.h"

typedef struct{
    UG_GUI* gui;
    oled_screen_t* oled;
    uint32_t last_tick;
}graphics_backend_t;


void graphics_backend_init(graphics_backend_t* backend, oled_screen_t* oled);
void graphics_backend_update(graphics_backend_t* backend, uint32_t current_tick);


#endif