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
    int x;
    int y;
    uint8_t* text;
    std::chrono::milliseconds time;
};

/* Declaration of threads */
Thread t1;
Thread t2;
Thread t3;

/*
 * @abstract Displays data on display with specific parameters
 * @param DispData *data 	Data structure with properties
 */
void vypis(DispData *data) {
    while (1) {
        BSP_LCD_DisplayStringAt(data->x,LINE(data->y), data->text, CENTER_MODE);
        ThisThread::sleep_for(data->time);
        BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
        BSP_LCD_ClearStringLine(data->y);
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        ThisThread::sleep_for(data->time);
    }
}

int main()
{
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
    /* Declaration & Definition of data in third thread */
    DispData data3;
        data3.x = X3;
        data3.y = Y3;
        data3.text = (uint8_t*) TEXT3;
        data3.time = T3;

    /* Start of threads */
    t1.start(callback(vypis, &data1));
    t2.start(callback(vypis, &data2));
    t3.start(callback(vypis, &data3));

    while (1) {
        HAL_Delay(2000);
    }
}
