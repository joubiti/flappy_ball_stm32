#include "oled.h"
#include "stm32g0xx.h"
#include "string.h"


/**
 * @brief Wrapper for SPI data transfer
 * 
 * @param spi_handle 
 * @param data 
 * @param nb_of_bytes 
 */
static inline void spi_transfer_bytes(SPI_HandleTypeDef* spi_handle, uint8_t* data, uint16_t nb_of_bytes);


/**
 * @brief Enter command mode
 * 
 */
static void oled_command_mode(void);

/**
 * @brief Enter data mode
 * 
 */
static void oled_data_mode(void);

/**
 * @brief Send an 8-bit command to the OLED display 
 * 
 * @param oled: OLED device
 * @param cmd: 8-bit command
 */
static void send_command(oled_screen_t* oled, uint8_t cmd);

/**
 * @brief Sends data to OLED
 * 
 * @param oled: OLED device
 * @param data: array of bytes
 * @param nb_of_bytes: number of bytes
 */
static void send_data(oled_screen_t* oled, uint8_t* data, uint8_t nb_of_bytes);

/**
 * @brief Resets OLED
 * 
 */
static void oled_reset(void);

void oled_initialize(oled_screen_t* oled, SPI_HandleTypeDef* spi){
    for(uint16_t j = 0; j < 1024; j ++){
        oled->fb[j] = 0;
    }
    oled->spi_handle = spi;
    oled_reset();
    HAL_Delay(100);

    send_command(oled, 0xAE); //display off
    send_command(oled, 0x20); //Set Memory Addressing Mode
    send_command(oled, 0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    send_command(oled, 0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    send_command(oled, 0xC8); //Set COM Output Scan Direction
    send_command(oled, 0x00); //---set low column address
    send_command(oled, 0x10); //---set high column address
    send_command(oled, 0x40); //--set start line address
    send_command(oled, 0x81); //--set contrast control register
    send_command(oled, 0xFF);
    send_command(oled, 0xA1); //--set segment re-map 0 to 127
    send_command(oled, 0xA6); //--set normal display
    send_command(oled, 0xA8); //--set multiplex ratio(1 to 64)
    send_command(oled, 0x3F); //
    send_command(oled, 0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    send_command(oled, 0xD3); //-set display offset
    send_command(oled, 0x00); //-not offset
    send_command(oled, 0xD5); //--set display clock divide ratio/oscillator frequency
    send_command(oled, 0xF0); //--set divide ratio
    send_command(oled, 0xD9); //--set pre-charge period
    send_command(oled, 0x22); //
    send_command(oled, 0xDA); //--set com pins hardware configuration
    send_command(oled, 0x12);
    send_command(oled, 0xDB); //--set vcomh
    send_command(oled, 0x20); //0x20,0.77xVcc
    send_command(oled, 0x8D); //--set DC-DC enable
    send_command(oled, 0x14); //
    send_command(oled, 0xAF); //--turn on SSD1306 panel
}

void oled_draw_pixel(oled_screen_t* oled, uint16_t x, uint16_t y, uint8_t color){
    uint16_t byte_idx = (y/8) * 128 + x;
    uint8_t bit_position = y % 8;
    if(color == 1){
        oled->fb[byte_idx] |= (1 << bit_position);
    }
    else{
        oled->fb[byte_idx] &= ~(1 << bit_position);
    }
}


void oled_update(oled_screen_t* oled){
    // In normal display data RAM read or write and page addressing mode, the following steps are required to
    // define the starting RAM access pointer location:
    // Set the page start address of the target display location by command B0h to B7h.
    // Set the lower start column address of pointer by command 00h~0Fh.
    // Set the upper start column address of pointer by command 10h~1Fh.
    // For example, if the page address is set to B2h, lower column address is 03h and upper column address is 10h,
    // then that means the starting column is SEG3 of PAGE2. The RAM access pointer is located as shown in
    // Figure 10-2. The input data byte will be written into RAM position of column 3.

    for (uint8_t page = 0; page < 8; page++) {          // Iterate through each of the 8 pages
        send_command(oled, 0xB0 + page);                      // Set page address (0xB0 is Page 0, 0xB1 is Page 1, etc.)
        send_command(oled, 0x00);                             // Set lower column address to 0
        send_command(oled, 0x10);                             // Set higher column address to 0

        send_data(oled, &oled->fb[page * 128], 128);
    }
}

void oled_clear_screen(oled_screen_t* oled) {
    // Set all bytes in the frame buffer to 0
    memset(oled->fb, 0, 1024);  // Clear the entire 1024-byte frame buffer

    // Send the cleared frame buffer to the OLED to update the display
    // oled_update(oled);
}


static void oled_command_mode(void){
    // set D/C pin to 0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
}

static void oled_data_mode(void){
    // set D/C pin to 1
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
}

static void send_command(oled_screen_t* oled, uint8_t cmd){
    oled_command_mode();
    spi_transfer_bytes(oled->spi_handle, &cmd, 1);
}

static void send_data(oled_screen_t* oled, uint8_t* data, uint8_t nb_of_bytes){
    oled_data_mode();
    spi_transfer_bytes(oled->spi_handle, data, nb_of_bytes);
}


static void oled_reset(void){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
    HAL_Delay(10);
}

static inline void spi_transfer_bytes(SPI_HandleTypeDef* spi_handle, uint8_t* data, uint16_t nb_of_bytes){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET);
    HAL_SPI_Transmit(spi_handle, data, nb_of_bytes, 50);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);
}