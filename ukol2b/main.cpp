#include "mbed.h"
#include "main.h"
#include "stm32746g_discovery_lcd.h"

/*
 * Support structure for displaying data on the display
 * @param x number of pixels
 * @param y line number
 * @param text displayed text
 * @param time sleep duration in milliseconds
   @param color HEX color of letters
   @param back_color HEX color of background
 */
struct DispData {
    int x;
    int y;
    uint8_t* text;
    std::chrono::milliseconds time;
    uint32_t color;
    uint32_t back_color;
};

// Mutex lock
Mutex mtx;

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
        mtx.lock();
        BSP_LCD_SetTextColor(data->color);
        BSP_LCD_SetBackColor(data->back_color);
        BSP_LCD_DisplayStringAt(data->x,LINE(data->y), data->text, CENTER_MODE);
        ThisThread::sleep_for(data->time);
        BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
        BSP_LCD_ClearStringLine(data->y);
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        ThisThread::sleep_for(data->time);
        mtx.unlock();
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
    
	
    /* Declaration & Definition of data in first thread */
    DispData data1;
        data1.x = X1;
        data1.y = Y1;
        data1.text = (uint8_t*) TEXT1;
        data1.time = T1;
        data1.color = C1;
        data1.back_color = B1;
    /* Declaration & Definition of data in second thread */
    DispData data2;
        data2.x = X2;
        data2.y = Y2;
        data2.text = (uint8_t*) TEXT2;
        data2.time = T2;
        data2.color = C2;
        data2.back_color = B2;
    /* Declaration & Definition of data in third thread */
    DispData data3;
        data3.x = X3;
        data3.y = Y3;
        data3.text = (uint8_t*) TEXT3;
        data3.time = T3;
        data3.color = C3;
        data3.back_color = B3;

    /* Start of threads */
    t1.start(callback(vypis, &data1));
    t2.start(callback(vypis, &data2));
    t3.start(callback(vypis, &data3));

    while (1) {
        HAL_Delay(2000);
    }
}
