#include "UART.h"


// These functions check if the UART is ready to send or receive data, they return 1 if ready, 0 if not.

bool UART1_isCharAvailable(void){
    return READ_BIT(UART1_FR_R, 4) == 0;             // Check if RXFE is 0 (data available)
}



bool UART1_isTxReady(void){
    return READ_BIT(UART1_FR_R, 5) == 0;             // Check if TXFF is 0 (transmit FIFO not full)
}




char UART1_getChar(void){
    while(UART1_isCharAvailable() == 0);             // Wait for character to be available
    return (char)(UART1_DR_R & 0xFF);                // Read character from UART1 data register
}

// sending data


void UART1_sendChar(char data){
    while(UART1_isTxReady() == 0);                   // Wait for transmit FIFO to be not full
    UART1_DR_R = data;                               // Send character to UART1 data register
}


void UART1_sendString(char *str){
    while(*str != '\0'){                             // Loop until null terminator is reached
        UART1_sendChar(*str);                        // Send each character
        str++;                                       // Move to the next character
   }
}
