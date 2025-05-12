#ifndef UART_H
#define UART_H

#include "../Utilities/tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdbool.h>
#include "../Utilities/bit_ops.h"

// Check data on Receiver

bool UART1_isCharAvailable(void);

// Check if Transmitter is ready to send data

bool UART1_isTxReady(void);

// Receive and Send data

char UART1_getChar(void);
void UART1_sendChar(char data);
void UART1_sendString(char *str);

#endif
