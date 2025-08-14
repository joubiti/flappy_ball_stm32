#ifndef _OLED_H
#define _OLED_H

#include "stm32g0xx_hal.h"

typedef struct{
    SPI_HandleTypeDef* spi_handle;
    uint8_t fb[1024];
}oled_screen_t;

/**
 * @brief Initialize OLED display over 4-wire SPI
 * 
 * @param oled: OLED device
 * @param spi_handle: SPI peripheral handle
 */
void oled_initialize(oled_screen_t* oled, SPI_HandleTypeDef* spi);

/**
 * @brief Draws a pixel in white in the specified x and y coordinates
 * 
 * @param oled: OLED device
 * @param x: column position
 * @param y: row position
 */
void oled_draw_pixel(oled_screen_t* oled, uint16_t x, uint16_t y, uint8_t color);

/**
 * @brief Update contents of OLED RAM display buffer
 * 
 * @param oled: OLED device
 */
void oled_update(oled_screen_t* oled);

/**
 * @brief Clear the display
 * 
 * @param oled: OLED device
 */
void oled_clear_screen(oled_screen_t* oled);

#endif