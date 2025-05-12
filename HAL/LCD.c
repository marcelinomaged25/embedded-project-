#include "LCD.h"

 ///////////////pin layout
//RS-->PD3
//RW-->PE1
//EN-->PD2

//D0-->PB3
//D1-->PC4
//D2-->PC5
//D3-->PC6
//D4-->PC7
//D5-->PD6
//D6-->PD7
//D7-->PF4


void printdata(unsigned char data){               // Sends byte to the LCD module through pins D0-->D7.

    if( (data & 0x01) == 0x01 ) SET_BIT(GPIO_PORTB_DATA_R,3); // Set PB3 if bit 0 of data is 1 (D0)
    else CLEAR_BIT(GPIO_PORTB_DATA_R,3);                  // Clear PB3 if bit 0 of data is 0

    if( (data & 0x02) == 0x02 )SET_BIT(GPIO_PORTC_DATA_R,4); // Set PC4 if bit 1 of data is 1 (D1)
    else CLEAR_BIT(GPIO_PORTC_DATA_R,4);                  // Clear PC4 if bit 1 of data is 0

    if( (data & 0x04) == 0x04 ) SET_BIT(GPIO_PORTC_DATA_R,5); // Set PC5 if bit 2 of data is 1 (D2)
    else CLEAR_BIT(GPIO_PORTC_DATA_R,5);                  // Clear PC5 if bit 2 of data is 0

    if( (data & 0x08) == 0x08 ) SET_BIT(GPIO_PORTC_DATA_R,6); // Set PC6 if bit 3 of data is 1 (D3)
    else CLEAR_BIT(GPIO_PORTC_DATA_R,6);                  // Clear PC6 if bit 3 of data is 0

    if( (data & 0x10) == 0x10 ) SET_BIT(GPIO_PORTC_DATA_R,7) ; // Set PC7 if bit 4 of data is 1 (D4)
    else CLEAR_BIT(GPIO_PORTC_DATA_R,7) ;                  // Clear PC7 if bit 4 of data is 0

    if( (data & 0x20) == 0x20 ) SET_BIT(GPIO_PORTD_DATA_R,6) ; // Set PD6 if bit 5 of data is 1 (D5)
    else CLEAR_BIT(GPIO_PORTD_DATA_R,6) ;                  // Clear PD6 if bit 5 of data is 0

    if( (data & 0x40) == 0x40 ) SET_BIT(GPIO_PORTD_DATA_R,7); // Set PD7 if bit 6 of data is 1 (D6)
    else CLEAR_BIT(GPIO_PORTD_DATA_R,7);                  // Clear PD7 if bit 6 of data is 0

    if( (data & 0x80) == 0x80 ) SET_BIT(GPIO_PORTF_DATA_R,4) ; // Set PF4 if bit 7 of data is 1 (D7)
    else CLEAR_BIT(GPIO_PORTF_DATA_R,4) ;                  // Clear PF4 if bit 7 of data is 0



}

void LCD_DATA(unsigned char data){                //Sends a data byte to the LCD module.

    SET_BIT(GPIO_PORTD_DATA_R,3);  //RS=1
    CLEAR_BIT(GPIO_PORTE_DATA_R,1); //RW=0
    printdata(data);                         //send an 8-bit data value to the LCD for display
    SET_BIT(GPIO_PORTD_DATA_R,2) ;  //EN=1
    delay(1);      //Delay/////////////////////////////////////////////////////////////////////////////////////////////change
    CLEAR_BIT(GPIO_PORTD_DATA_R,2); //EN=0
    delay(1);      //Delay/////////////////////////////////////////////////////////////////////////////////////////////change



    /* Control Signals:
    * - RS (Register Select): Set to 1 to indicate data register.
    * - RW (Read/Write): Set to 0 to indicate a write operation.
    * - EN (Enable): A high-to-low pulse to latch the data into the LCD.
    */

    }


void LCD_CRL(unsigned char cmd){                  //Sends a command byte to the LCD module.

    CLEAR_BIT(GPIO_PORTD_DATA_R,3); //RS=0
    CLEAR_BIT(GPIO_PORTE_DATA_R,1); //RW=0
    printdata(cmd); //send an 8-bit command value to the LCD for execution                     
    SET_BIT(GPIO_PORTD_DATA_R,2);  //EN=1
    delay(5);
    CLEAR_BIT(GPIO_PORTD_DATA_R,2); //EN=0
    delay(5);     //Delay
    
    /** Control Signals:
    * - RS (Register Select): Set to 0 to indicate a command is being sent.
    * - RW (Read/Write): Set to 0 to indicate a write operation.
    * - EN (Enable): Pulsed high to latch the command into the LCD.
    *
    */
}





void LCD_output(char *str) {   // Sends a null-terminated string to the LCD module as data bytes.

    while(*str != '\0') {
        LCD_DATA(*str);  // Send current character to LCD
        str++;           // Move to next character
    }

    /*
    * @param str Pointer to a null-terminated string to be displayed on the LCD.
    * The function stops when it reaches the '\0' character.
    */
}



void LCD_init(void){                              // Initialize the LCD module

    // Send initialization commands to the LCD

    LCD_CRL(0x38); // Function set: 8-bit mode, 2 lines, 5x7 dots
    LCD_CRL(0x06); // Entry mode set: increment cursor, no shift
    LCD_CRL(0x0C); // Display on, cursor off, blink off
    LCD_clear; 
    LCD_first; 

}
