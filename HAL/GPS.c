#include "GPS.h"


char GPS[82];
char GPS_logname[]="$GPRMC,";


char GPS_formated [12][20];
char * token;
float  LAT , LONG;
int    X = 0;
float  M = 0.0;


const double Earth_Radius=6371000;
void GPS_read(void)
{

	char recieved_char , fill_gps_counter = 0;
	char i = 0;
	//check that the logname recieved is the gps_logname
	char flag = 1;
	do
		{
			flag=1;
			for (i = 0;i<7;i++)
			{
				if (UART1_getChar()!= GPS_logname[i])
				{
					flag=0;
					break;
				}
			}
		}while(flag==0);

	strcpy(GPS,"");
	do
		{
			recieved_char = UART1_getChar();
			GPS[fill_gps_counter++] = recieved_char;
			
		}
	while(recieved_char != '*');
}

float dist_to_degree(float angle)
{
	int degree = (int)(angle / 100);
	float minutes = angle - (degree * 100);
	return degree + (minutes / 60.0f);
}
float degree_to_rad(float angle)
{
	return angle*(float)pi/180;
}

//A--> current location(latitude,longtude)
//B--> final location(latitude,longtude)
//phi A--> latitude A in rad
//phi B--> latitude B in rad
//lamda A--> longitude A in rad
//lamda B--> longitude B in rad

float GPS_get_distance(float LAT,float LONG ,float LAT_2,float LONG_2)          //parameters will be sended using gps module
{
	//get phi and lamda
	float phi_A = degree_to_rad(LAT);
	float phi_B = degree_to_rad(LAT_2);
	float lambda_A = degree_to_rad(LONG);
	float lambda_B = degree_to_rad(LONG_2);

	
	//get diffrences
	float lat_diff = phi_B - phi_A;
	float long_diff = lambda_B - lambda_A;

	
	//calculate the distance
	float a = pow(sin(lat_diff / 2), 2) + cos(phi_A) * cos(phi_B) * pow(sin(long_diff / 2), 2);
	float c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return Earth_Radius * c;
}

void GPS_format(void)
{
	char no_OF_strings = 0;
	token = strtok(GPS,",");
	do
	{
		strcpy (GPS_formated[no_OF_strings] , token);
		token = strtok(NULL , ",");
		no_OF_strings++;
	}
	while(token != NULL);
	
		if (strcmp (GPS_formated[1] , "A") == 0)           //A means valid
		{
			if (strcmp (GPS_formated[3] , "N") == 0)         //N for north (Positive)
			{
				LAT = atof (GPS_formated[2]);
			}
			else                                             //south (Negaative)
			{
				LAT = - atof (GPS_formated[2]);
			}
			if (strcmp (GPS_formated[5] , "E") == 0)         //E for east (positive)
			{
				LONG = atof (GPS_formated[4]);
			}
			else                                             //West (Negative)
			{
				LONG = - atof (GPS_formated[4]);
			}
	}
	X = LAT/100 ;
	M = LAT - X*100;
	LAT = X + M/60;
	X = LONG/100 ;
	M=LONG-X*100;
	LONG = X+M/60 ;
}
