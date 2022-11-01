#include "mbed.h"
#include "stm32746g_discovery_lcd.h"

int main()
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

    while (1) {
        BSP_LCD_Clear(LCD_COLOR_BLACK);
        BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

        BSP_LCD_DisplayStringAt(0, 1, (uint8_t *)"Martin a Daniel", CENTER_MODE);
        HAL_Delay(2000);
    }
}
