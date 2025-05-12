#include "../HAL/LCD.h"
#include "../HAL/GPS.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 16
//======================================================================================
	typedef struct {
    char name[NAME_LENGTH];
    float latitude;
    float longitude;
} landmarks;
    landmarks y[7] = {
			  
				{"Credit Building", 30.063362, 31.278526},
				{"Hall C,D" ,30.063675, 31.280571},
        {"Gate 2", 30.064625, 31.277270},
        {"Main Building", 30.064784, 31.279112},
        {"Mosque", 30.0646420, 31.2804053},
        {"water Fountain", 30.065563, 31.278402},
        {"Luban Workshop", 30.063411, 31.279507}
};
//============================================================================================
void All_Ports_Init(void)
	{
	    PortB_init();
	    PortC_init();
	    PortD_init();
	    PortE_init();
	    PortF_init();
	}
//===========================================================================================
void start_app(void) {
	LCD_init();
	LCD_clear;//clear display
	LCD_output("Waiting for GPS");
	delay(1000); // 1 sec

	GPS_read();
	GPS_format();

}
//===========================================================================================

int main(void)
{
	  float d= 0.0;
    int i = 0;
	  float min_dist = 100000.0;
	  int nearest_index = -1;

	All_Ports_Init();
	start_app();

	//===========================================================================================
	
	while (1)
	{
		
		// disable all leds and buzzer 
		red_led(0);
		green_led(0);
		blue_led(0);
		buzzer_alarm(0);
		
		GPS_read();
		GPS_format(); // Updates LAT, LONG

		if (LAT == 0 || LONG == 0) {
			LCD_clear;
			LCD_output("Waiting for GPS");
			delay(1000); // 1 sec
			continue; // Invalid GPS data, skip this loop
		}

		for (i = 0; i < 7; i++) {
			d = GPS_get_distance(LAT, LONG, y[i].latitude, y[i].longitude);
			if (d < min_dist) {
				min_dist = d;
				nearest_index = i;
			}
		} 
			char distance_str[16]; // Buffer to hold the formatted distance string

		sprintf(distance_str, "%.3f", min_dist); // Convert float to string with 3 decimal places 
		
		// if Gate 2 is the nearest buzzer alerts and red led on and display distance
		
if (strcmp (y[nearest_index].name , "Gate 2") == 0){
		buzzer_alarm(1);
	  red_led(1);
		LCD_clear;
    LCD_output("You are near");
		LCD_endl;
		LCD_output(y[nearest_index].name);
	  delay(3000);
	
	// outputs the distance
	
		LCD_clear;
		LCD_output("Distance = ");
		LCD_endl ;		
		LCD_output(distance_str);
		LCD_output(" m"); //meters

		delay(3000); // 3 secs
		LCD_clear;
}
		// else turn on green led and display distance

	else
{	
		green_led(1);
		LCD_clear;
    LCD_output("You are near");
		LCD_endl;
		LCD_output(y[nearest_index].name);
		delay(3000); // 3 secs
		LCD_clear;
		
		green_led(1);	// turn on green led		
				
		
		// outputs the distance
		
		LCD_output("Distance = ");
		LCD_endl ;		
		LCD_output(distance_str);
		LCD_output(" m"); //meters

		delay(3000); // 3 secs
		}
	
	}

}

