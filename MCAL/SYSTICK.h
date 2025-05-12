#ifndef SYSTICK_H
#define SYSTICK_H

#include "../Utilities/tm4c123gh6pm.h"


#define CLK 16000 // Assuming 16 MHz clock, 1 ms = 16000 ticks



void Systick_init(void);
void delay(unsigned int delay);
void wait_1ms(void);


#endif
