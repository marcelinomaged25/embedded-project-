#ifndef GPS_h
#define GPS_h

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../MCAL/UART.h"
#include "../Utilities/tm4c123gh6pm.h"


#define  pi 3.14159265
extern char GPS_formated [12][20];
extern char GPS[82];
extern float LAT;
extern float LONG;
void GPS_read(void);
float dist_to_degree(float angle);
float degree_to_rad(float angle);
float GPS_get_distance(float LAT,float LONG ,float LAT_2,float LONG_2);
void GPS_format(void);


#endif

