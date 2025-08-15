```
  _____.__                               ___.          .__  .__   
_/ ____\  | _____  ______ ______ ___.__. \_ |__ _____  |  | |  |  
\   __\|  | \__  \ \____ \\____ <   |  |  | __ \\__  \ |  | |  |  
 |  |  |  |__/ __ \|  |_> >  |_> >___  |  | \_\ \/ __ \|  |_|  |__
 |__|  |____(____  /   __/|   __// ____|  |___  (____  /____/____/
                 \/|__|   |__|   \/           \/     \/
```

A rather crude implementation of the flappy bird (ball) game on an STM32G070 microcontroller in C

![Flappy Ball Demo](demo/flappy-ball-demo.gif)

## Architecture

In an attempt to have a modular codebase with clear separation of game logic, graphics rendering and hardware drivers, I've written the "game engine" as a state machine that in turn makes calls to the game renderer module for displaying the game dynamics on the OLED screen.

Ball and pipes are modeled as objects in the code, with some tuneable parameters for gravity and velocity effects.

As such, the main while-loop is reduced to being a very simplistic superloop:
```
while(1){
    oled_clear_screen(&oled);
    
    /* Dispatch button press event to the game engine state machine */
    game_engine_step(is_button_pressed(&user_btn, HAL_GetTick()));

    /* Toggle Heartbeat LED (1 Hz) */
    heartbeat_led_toggle(&heartbeat_led, HAL_GetTick());

    /* Update graphics (50 Hz), using low-level OLED calls and µGUI */
    graphics_backend_update(&backend, HAL_GetTick());
  }
```
µGUI was used at the embedded GUI graphics library of choice because it's lightweight and because we don't need much for this game, so I've had the write the graphics backend module to plug our pixel OLED functions to the µGUI library.
Very simple, and very cool.

```
static void backend_draw_pixel(UG_S16 x, UG_S16 y, UG_COLOR color)
{
    uint8_t oled_color = (color != C_BLACK) ? 1 : 0;
    oled_draw_pixel(s_oled, (uint16_t)x, (uint16_t)y, oled_color);
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
```

The rest is self explanatory I'd hope, I sprinkled a bit of Doxygen style comments all over the code to make it more readable for people (and for myself).

## Build the project

I used a Nucleo board to prototype this: https://www.st.com/en/evaluation-tools/nucleo-g070rb.html
And an SSD1306 OLED breakout board from Adafruit (the SPI one).
Hardware pins are provided in the code, and also in the .mx file inside the top level directory.

A Makefile is provided, so all you need to do to compile is create a "build" folder, then run:
```
make
```
Assuming you have already installed the arm-gcc-none-eabi cross compiler and added it to your PATH.

For flashing, I use OpenOCD directly from VSCode with Cortex-Debug, the relevant files are in .vscode folder and must probably be tweaked to match your build machine.
