/* Copyright 2018 Flora Canou, Alexander Zheng | V. C3-C3 (1.1.0) | Improved HCI to RGB Convertor
 * This Source Code Form is licensed under the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, you can obtain one at https://mozilla.org/MPL/2.0/. 
 * The program converts an entry in an Improved HCI color model to the corresponding RGB representation. 
 * See Improved HCI Color Model Specifications for more info. 
 */

#include <stdio.h>
#include <math.h>
#define pi	3.14159265

void ihciBack (double h, double c, double i, double *p1, double *p2, double *p3)
{
	*p1 = i + 2 * c * cos (h) / 3;
	*p2 = i + 2 * c * cos (h - 2 * pi / 3) / 3;
	*p3 = i + 2 * c * cos (h - 4 * pi / 3) / 3;
}

void instruct (void);
int main (void)
{
	instruct();
	double h, c, i; //hue in degrees, intensity, chroma
	double r, g, b; //red, green, blue
	
	while (1)
	{
		printf ("Please enter the values. > ");
		scanf ("%lf %lf %lf", &h, &c, &i);
		if (h == -1 && c == -1 && i == -1)
			return 0;
		else if (h < 0 || c < 0 || i < 0 || h > 360 || c > 1 || i > 1)
			printf ("Warning: One or more values are out of range. The result may be erroneous. \n");
		
		h = h * pi / 180; //degree to radian
		ihciBack (h, c, i, &r, &g, &b);
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

