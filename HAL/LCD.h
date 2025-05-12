#ifndef LCD_H
#define LCD_H

#include <stdbool.h>
#include "../MCAL/SYSTICK.h"
#include "../Utilities/tm4c123gh6pm.h"
#include "../MCAL/GPIO.h"
#include "../Utilities/bit_ops.h"


#define LCD_clear LCD_CRL(0x01)   //clears the LCD screen
#define LCD_first LCD_CRL(0x80)  // move to first line 
#define LCD_endl  LCD_CRL(0xC0)  // move to the next line of lcd



void printdata(unsigned char data);// Sends a data byte to the LCD module through pins D0-->D7.

void LCD_DATA(unsigned char data);// Sends a data byte to the LCD module.

void LCD_CRL(unsigned char cmd);// Sends a command byte to the LCD module.

void LCD_output(char *str );// Sends a string to the LCD module.

void LCD_init(void);// Initializes the LCD module.


#endif



