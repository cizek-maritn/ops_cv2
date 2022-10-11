/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "main.h"
#include <cstring>

// Global variable of the LED
DigitalOut led(LED1);

/*
    @abstract turns on the LED for a long time 
*/

void lblink() {
    led = DIODA_ON;
    ThisThread::sleep_for(LONG_BLINK_TIME);
    led = DIODA_OFF;
    ThisThread::sleep_for(LETTER_SEPARATOR_TIME);
}
/*
    @abstract turns on the LED for a short time 
*/
void sblink() {
    led = DIODA_ON;
    ThisThread::sleep_for(SHORT_BLINK_TIME);
    led = DIODA_OFF;
    ThisThread::sleep_for(LETTER_SEPARATOR_TIME);
}

/*
    @abstract Makes blink a letter LED with Morse alphabet
    @param char letter - input letter
*/
void blink(char letter) {
    switch (letter) {
        case 'a':
            sblink();
            lblink();
            break;
        case 'd':
            lblink();
            sblink();
            sblink();
            break;
        case 'e':
            sblink();
            break;
        case 'i':
            sblink();
            sblink();
            break;
        case 'l':
            sblink();
            lblink();
            sblink();
            sblink();
            break;
        case 'n':
            lblink();
            sblink();
            break;
        case 's':
            sblink();
            sblink();
            sblink();
            break;
        case 'o':
            lblink();
            lblink();
            lblink();
            break;
        case 'm':
            lblink();
            lblink();
            break;
        case 'r':
            sblink();
            lblink();
            sblink();
            break;
        case 't':
            lblink();
            break;
    }
}

int main() {
    while (true) {
        // Input string
        char* slovo = "sos";

        // loop char by char and makes blink
        for (int i = 0; i < strlen(slovo); i++)
            blink(slovo[i]);
        // word separator
        ThisThread::sleep_for(LETTER_SEPARATOR_TIME*2);
    }
}
