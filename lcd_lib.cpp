#include <stdint.h>
#include "stm32746g_discovery_lcd.h"

enum position {
    LEFT = LEFT_MODE,
    CENTER = CENTER_MODE,
    RIGHT = RIGHT_MODE
}
void print_at(uint16t xpos, uint16_t ypos, uint8_t* sentence, position pos) {
    switch(position) {
        case LEFT:
            print_left(xpos, ypos, sentence);
            break;
        case CENTER:
            print_center(xpos, ypos, sentence);
            break;
        case RIGHT:
            print_right(xpos, ypos, sentence);
            break;
    }
}
void print_left(uint16t xpos, uint16_t ypos, uint8_t* sentence) { BSP_LCD_DisplayStringAt(xpos, ypos, sentence, LEFT_MODE); }
void print_center(uint16t xpos, uint16_t ypos, uint8_t* sentence) { BSP_LCD_DisplayStringAt(xpos, ypos, sentence, CENTER_MODE); }
void print_right(uint16t xpos, uint16_t ypos, uint8_t* sentence) { BSP_LCD_DisplayStringAt(xpos, ypos, sentence, RIGHT_MODE); }
