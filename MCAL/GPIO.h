#ifndef GPIO_H
#define GPIO_H

#include "../Utilities/tm4c123gh6pm.h"
#include "../MCAL/GPIO.h"
#include <stdbool.h>
#include "../Utilities/bit_ops.h"
#include <stdbool.h>


void PortB_init(void); // GPIO for LCD + UART
void PortC_init(void); // GPIO for LCD
void PortD_init(void); // GPIO for LCD
void PortF_init(void); // GPIO for LCD + LEDs 
void PortE_init(void); // GPIO for LCD + buzzer


// LED Control Functions for Port F
void red_led(bool state);
void green_led(bool state);
void blue_led(bool state);

//buzzer control Function for Port E
void buzzer_alarm(bool state);


#endif
