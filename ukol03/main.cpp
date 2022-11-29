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
    std::chrono::milliseconds time;
    uint32_t color;
    uint32_t back_color;
};

// Mutex lock
Mutex mtx;

// Declaration of threads
Thread t1, t2, t3, t4, t5, t6;

// Declaration of semaphore
Semaphore semaphore(SIZE_OF_PARKING);

// Shared memory
bool parking_slots[SIZE_OF_PARKING] = {false};

/* 
 * @abstract Find free slot
 * @return index of free slot OR -1 if occupied
 */
uint16_t findFreeSlot() {
    for (uint16_t i = 0; i < SIZE_OF_PARKING; i++)
        // TRUE = occupied ; FALSE = free
        if (!parking_slots[i]) return i+1;
    return 0;
}

void clearDisplay() { BSP_LCD_Clear(LCD_COLOR_BLACK); }
void clearLine(char y) { BSP_LCD_ClearStringLine(y); }
/*
 * @abstract Displays data on display with specific parameters
 * @param DispData *data 	Data structure with properties
 */
void vypis(DispData *data) {
    while (true) {
        semaphore.acquire();
        mtx.lock();
        uint16_t slot = findFreeSlot();
        if (slot != 0) {
            // Set slot occupied
            parking_slots[slot-1] = true;

            // Printing on the display
            BSP_LCD_SetTextColor(data->color);
            BSP_LCD_SetBackColor(data->back_color);
            BSP_LCD_DisplayStringAt(data->x,LINE(slot), data->text, CENTER_MODE);
            mtx.unlock();

            ThisThread::sleep_for(data->time);

            mtx.lock();
            BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
            clearLine(LINE(slot));   

            // Set slot free
            parking_slots[slot-1] = false;
            mtx.unlock();
        } else {
            mtx.unlock();
        }
        semaphore.release();
    }
}

int main() {
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

    /* Declaration & Definition of data in thread */
    DispData data1;
        data1.x = X1;
        data1.text = (uint8_t*) TEXT1;
        data1.time = T1;
        data1.color = C1;
        data1.back_color = B1;
    DispData data2;
        data2.x = X2;
        data2.text = (uint8_t*) TEXT2;
        data2.time = T2;
        data2.color = C2;
        data2.back_color = B2;
    DispData data3;
        data3.x = X3;
        data3.text = (uint8_t*) TEXT3;
        data3.time = T3;
        data3.color = C3;
        data3.back_color = B3;
    DispData data4;
        data4.x = X4;
        data4.text = (uint8_t*) TEXT4;
        data4.time = T4;
        data4.color = C4;
        data4.back_color = B4;
    DispData data5;
        data5.x = X5;
        data5.text = (uint8_t*) TEXT5;
        data5.time = T5;
        data5.color = C5;
        data5.back_color = B5;
    DispData data6;
        data6.x = X6;
        data6.text = (uint8_t*) TEXT6;
        data6.time = T6;
        data6.color = C6;
        data6.back_color = B6;

    /* Start of threads */
    t1.start(callback(vypis, &data1));
    t2.start(callback(vypis, &data2));
    t3.start(callback(vypis, &data3));
    t4.start(callback(vypis, &data4));
    t5.start(callback(vypis, &data5));
    t6.start(callback(vypis, &data6));
    
    while (true) {}
}
