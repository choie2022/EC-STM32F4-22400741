
// /*----------------------------------------------------------------\
// @ Embedded Controller by Young-Keun Kim - Handong Global University
// Author           : [ Erin Choi]
// Created          : 05-03-2021
// Modified         : 09-18-2026]
// Language/ver     : C++ in VS Code

// Description      : Code to turn LED one at a time in order, using button
// /----------------------------------------------------------------*/
#include "ecRCC2.h"
#include "ecGPIO2.h"

#define BUTTON_PIN  PA_4

PinName_t leds[4] = {PB_12, PB_13, PB_14, PB_15};

void setup(void) {
    RCC_HSI_init();

    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PU);

    for (int i = 0; i < 4; i++) {
        GPIO_init(leds[i], OUTPUT);
        GPIO_pupd(leds[i], PU);
        GPIO_otype(leds[i], OD);
        GPIO_ospeed(leds[i], MID);
        GPIO_write(leds[i], LOW);
    }
}

int main(void) {
    setup();
    int count = -1;

    while (1) {
        if (GPIO_read(BUTTON_PIN) == 0) {
            count = (count + 1) % 4;

            for (int i = 0; i < 4; i++) {
                if (i == count) GPIO_write(leds[i], HIGH);
                else            GPIO_write(leds[i], LOW);
            }

            while (GPIO_read(BUTTON_PIN) == 0);
            delay_ms_HSI(20);
        }
    }
}