#include "GPIO.h"



void PortB_init(void){
    SET_BIT(SYSCTL_RCGCGPIO_R, 1);                   // Enable clock for Port B
    while(READ_BIT(SYSCTL_PRGPIO_R, 1) == 0){};      // Wait for clock stabilization

    SET_BIT(SYSCTL_RCGCUART_R, 1);                   // Enable clock for UART1
    while(READ_BIT(SYSCTL_PRUART_R, 1) == 0){};      // Wait for UART clock to stabilize

    GPIO_PORTB_LOCK_R = 0x4C4F434B;                  // Unlock Port B configuration
    GPIO_PORTB_CR_R = 0x0B;                          // Allow changes to PB0, PB1, and PB3

    GPIO_PORTB_DEN_R = 0x0B;                         // Enable digital functionality for PB0, PB1, PB3
    GPIO_PORTB_DIR_R = 0x0B;                         // Set PB0, PB1, PB3 as outputs

    GPIO_PORTB_AMSEL_R = 0x00;                       // Disable analog functionality
    GPIO_PORTB_PCTL_R = 0x00000011;                  // Configure pin control for UART function
    GPIO_PORTB_AFSEL_R = 0x03;                       // Enable alternate function for PB0-PB1

    CLEAR_BIT(UART1_CTL_R, 0);                       // Disable UART1 during configuration
    CLEAR_BIT(UART1_CTL_R, 8);
    CLEAR_BIT(UART1_CTL_R, 9);
    
    UART1_IBRD_R = 104;                              // Configure baud rate (integer part)
    UART1_FBRD_R = 11;                               // Configure baud rate (fractional part)
    
    UART1_LCRH_R = 0x70;                             // Configure UART parameters (8N1 with FIFOs)
    
    SET_BIT(UART1_CTL_R, 0);                         // Enable UART1
    SET_BIT(UART1_CTL_R, 8);                         // Enable transmitter 
    SET_BIT(UART1_CTL_R, 9);                         // Enable receiver
}

void PortC_init(void){
    SET_BIT(SYSCTL_RCGCGPIO_R, 2);                   // Enable clock for Port C
    while(READ_BIT(SYSCTL_PRGPIO_R, 2) == 0){};      // Wait for clock stabilization
    
    GPIO_PORTC_LOCK_R = 0x4C4F434B;                  // Unlock Port C configuration
    GPIO_PORTC_CR_R = 0xF0;                          // Allow changes to PC4-PC7
    
    GPIO_PORTC_AMSEL_R = 0x00;                       // Disable analog functionality
    GPIO_PORTC_PCTL_R = 0x00000000;                  // Use default GPIO settings
    GPIO_PORTC_AFSEL_R = 0x00;                       // Disable alternate functions
    
    GPIO_PORTC_DEN_R = 0xFF;                         // Enable digital I/O for all PC pins
    GPIO_PORTC_DIR_R = 0xFF;                         // Set all PC pins as outputs
}

void PortD_init(void){
    SET_BIT(SYSCTL_RCGCGPIO_R, 3);                   // Enable clock for Port D
    while(READ_BIT(SYSCTL_PRGPIO_R, 3) == 0){};      // Wait for clock stabilization
    
    GPIO_PORTD_LOCK_R = 0x4C4F434B;                  // Unlock Port D configuration
    GPIO_PORTD_CR_R = 0xCC;                          // Allow changes to PD2, PD3, PD6, PD7
    
    GPIO_PORTD_AMSEL_R = 0x00;                       // Disable analog functionality
    GPIO_PORTD_PCTL_R = 0x00000000;                  // Use default GPIO settings
    GPIO_PORTD_AFSEL_R = 0x00;                       // Disable alternate functions
    
    GPIO_PORTD_DEN_R = 0xCC;                         // Enable digital I/O for selected pins
    GPIO_PORTD_DIR_R = 0xCC;                         // Set selected pins as outputs
}

void PortE_init(void){
    SET_BIT(SYSCTL_RCGCGPIO_R, 4);                   // Enable clock for Port E
    while(READ_BIT(SYSCTL_PRGPIO_R, 4) == 0){};      // Wait for clock stabilization
    
    GPIO_PORTE_LOCK_R = 0x4C4F434B;                  // Unlock Port E configuration
    GPIO_PORTE_CR_R = 0x0A;                          // Allow changes to PE1 and PE3 
    
    GPIO_PORTE_AMSEL_R = 0x00;                       // Disable analog functionality
    GPIO_PORTE_PCTL_R = 0x00000000;                  // Use default GPIO settings
    GPIO_PORTE_AFSEL_R = 0x00;                       // Disable alternate functions
    
    GPIO_PORTE_DEN_R = 0x0A;                         // Enable digital I/O for PE1 and PE3
    GPIO_PORTE_DIR_R = 0x0A;                         // Set PE1 and PE3  as output
}

void PortF_init(void){
    SET_BIT(SYSCTL_RCGCGPIO_R, 5);                   // Enable clock for Port F
    while(READ_BIT(SYSCTL_PRGPIO_R, 5) == 0){};      // Wait for clock stabilization
    
    GPIO_PORTF_LOCK_R = 0x4C4F434B;                  // Unlock Port F configuration
    GPIO_PORTF_CR_R = 0x1F;                          // Allow changes to PF0-PF4
    
    GPIO_PORTF_AMSEL_R = 0x00;                       // Disable analog functionality
    GPIO_PORTF_PCTL_R = 0x00000000;                  // Use default GPIO settings
    GPIO_PORTF_AFSEL_R = 0x00;                       // Disable alternate functions
    
    GPIO_PORTF_DEN_R = 0x1F;                         // Enable digital I/O for PF0-PF4
    GPIO_PORTF_DIR_R = 0x1F;                         // Set PF0-PF4 as outputs
}




// Functions for LED control

void red_led(bool state) {
    if (state) {
        SET_BIT(GPIO_PORTF_DATA_R, 1);               // Turn on red LED (PF1)
    } else {
        CLEAR_BIT(GPIO_PORTF_DATA_R, 1);             // Turn off red LED (PF1)
    }
}

void green_led(bool state) {
    if (state) {
        SET_BIT(GPIO_PORTF_DATA_R, 3);               // Turn on green LED (PF3)
    } else {
        CLEAR_BIT(GPIO_PORTF_DATA_R, 3);             // Turn off green LED (PF3)
    }
}

void blue_led(bool state) {
    if (state) {
        SET_BIT(GPIO_PORTF_DATA_R, 2);               // Turn on blue LED (PF2)
    } else {
        CLEAR_BIT (GPIO_PORTF_DATA_R, 2);             // Turn off blue LED (PF2)
   }
}


// Function for Buzzer control

void buzzer_alarm(bool state) {
    if (state)
        SET_BIT(GPIO_PORTE_DATA_R,3);
        else
            CLEAR_BIT(GPIO_PORTE_DATA_R,3);
}
