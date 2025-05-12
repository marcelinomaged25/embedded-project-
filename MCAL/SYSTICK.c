#include "SYSTICK.h"


void Systick_init(void) {
    NVIC_ST_CTRL_R = 0; // Disable Systick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // Set reload value to max
    NVIC_ST_CURRENT_R = 0; // Clear current value
    NVIC_ST_CTRL_R = 0x00000005; // Enable SysTick with core clock
}


void wait_1ms(void) {
    NVIC_ST_CTRL_R = 0; // Disable SysTick during setup
    NVIC_ST_RELOAD_R = CLK - 1; // Set reload value for 1 ms
    NVIC_ST_CURRENT_R = 0; // Clear current value
    NVIC_ST_CTRL_R |= 0x00000005; // Enable SysTick timer

    while ((NVIC_ST_CTRL_R & 0x00010000) == 0); // Wait for COUNT flag
    NVIC_ST_CTRL_R = 0; // Disable Systick after delay
}

void delay(unsigned int delay) {
    
    for(int i = 0; i < delay; i++) {
        wait_1ms(); 
    }

}
