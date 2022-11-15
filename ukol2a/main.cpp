#include "mbed.h"
#include "main.h"
#include "stm32746g_discovery_lcd.h"

/*
 * Support structure for displaying data on the display
 * @param x number of pixels
 * @param y line number
 * @param text displayed text
 * @param time sleep duration in milliseconds
 */
struct DispData {
    uint16_t x;
    uint16_t y;
    uint8_t* text;
    uint32_t time;
};

/* Declaration of threads */
Thread t1;
Thread t2;

void clearDisplay() { BSP_LCD_Clear(LCD_COLOR_BLACK); }
/*
 * @abstract Displays data on display with specific parameters
 * @param DispData *data 	Data structure with properties
 */
void vypis(DispData *data) {
    BSP_LCD_DisplayStringAt(data->x,LINE(data->y), data->text, CENTER_MODE);
    HAL_Delay(data->time);
    clearDisplay();
}

int main() {
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

    /* Declaration & Definition of data in first thread */
    DispData data1;
        data1.x = X1;
        data1.y = Y1;
        data1.text = (uint8_t*) TEXT1;
        data1.time = T1;
    /* Declaration & Definition of data in second thread */
    DispData data2;
        data2.x = X2;
        data2.y = Y2;
        data2.text = (uint8_t*) TEXT2;
        data2.time = T2;

    /* Start of threads */
    t1.start(callback(vypis, &data1));
    t1.join();
    
    t2.start(callback(vypis, &data2));
    t2.join();
}
