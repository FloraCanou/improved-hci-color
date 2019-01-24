/* Copyright 2018 Flora Canou, Alexander Zheng | V. C4-1.2.0 | Improved HCI to RGB Convertor
 * This Source Code Form is licensed under the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, you can obtain one at https://mozilla.org/MPL/2.0/. 
 * The program converts an entry in an Improved HCI color model to the corresponding RGB representation. 
 * See Improved HCI Color Model Specifications for more info. 
 */

#include <stdio.h>
#include <math.h>
#define pi	3.14159265359

void ihciBack (double H, double C, double I, double *p1, double *p2, double *p3)
{
	*p1 = I + 2*C*cos (H) / 3;
	*p2 = I + 2*C*cos (H - 2*pi / 3) / 3;
	*p3 = I + 2*C*cos (H + 2*pi / 3) / 3;
}

void instruct (void);
int main (void)
{
	instruct();
	double H, C, I; //hue in degrees, intensity, chroma
	double r, g, b; //red, green, blue
	
	while (1)
	{
		printf ("Please enter the values. > ");
		scanf ("%lf %lf %lf", &H, &C, &I);
		if (H == -1 && C == -1 && I == -1)
			return 0;
		else if (H < 0 || C < 0 || I < 0 || H > 360 || C > 1 || I > 1)
			printf ("Warning: One or more values are out of range. The result may be erroneous. \n");
		
		H = H*pi / 180; //degree to radian
		ihciBack (H, C, I, &r, &g, &b);
		printf ("Red\t= %f, \nGreen\t= %f, \nBlue\t= %f. \n", r, g, b);
	}
}

void instruct (void)
{
	printf ("This program converts an entry in an Improved HCI color model to the corresponding RGB representation. \n"
			"You will be asked to enter the values for hue, chroma and intensity, respectively. \n"
			"The hue should be in degrees, between 0 and 360. The other two should be between 0 and 1. \n"
			"Note: In case the hue is undefined, enter any value for hue and 0 for chroma. \n"
			"All of them should be separated with a space. Enter -1 -1 -1 to exit. \n\n");
}

