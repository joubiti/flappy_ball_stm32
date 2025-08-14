#include "graphics_backend.h"

#define USE_FONT_6X10

static UG_GUI gui;
static oled_screen_t* s_oled = NULL;

static void backend_draw_pixel(UG_S16 x, UG_S16 y, UG_COLOR color)
{
    // uint8_t oled_color = (color == C_WHITE) ? 1 : 0;
    oled_draw_pixel(s_oled, (uint16_t)x, (uint16_t)y, 1);
}

void graphics_backend_init(graphics_backend_t* backend, oled_screen_t* oled)
{
    backend->oled = oled;
    backend->gui = &gui;
    s_oled = backend->oled;
    UG_Init(backend->gui, backend_draw_pixel, 128, 64);

    UG_FontSelect(&FONT_6X10);
}


void graphics_backend_update(graphics_backend_t* backend, uint32_t current_tick)
{
    if(current_tick - backend->last_tick >= 20)
    {
        UG_Update();
        oled_update(backend->oled);
        backend->last_tick = current_tick;
    }

}
