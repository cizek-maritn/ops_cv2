#include "mbed.h"
#include "main.h"
#include <cstring>


DigitalOut myled(LED1);

void lblink() {
    myled = DIODA_ON;
    wait(LONG);
    myled = DIODA_OFF;
    wait(SEPARATOR);
}
void sblink() {
    myled = DIODA_ON;
    wait(SHORT);
    myled = DIODA_OFF;
    wait(SEPARATOR);

}

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
    while(1) {
        char* slovo = "sos";

        for (int i = 0; i < strlen(slovo); i++)
            blink(slovo[i]);
        // WORD SEPARATOR DELAY
        wait(SEPARATOR*2);

        //myled = 1; // LED is ON
        //wait(0.2); // 200 ms
        //myled = 0; // LED is OFF
        //wait(1.0); // 1 sec
    }
}
