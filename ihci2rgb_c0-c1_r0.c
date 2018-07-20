/* Copyright 2018 Flora Canou, Alexander Zheng | V. C0-C1 (1.0.1) | Improved HCI to RGB Convertor
 * This Source Code Form is licensed under the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, you can obtain one at https://mozilla.org/MPL/2.0/. 
 * The program converts an entry in an Improved HCI color space to the corresponding RGB representation. 
 * See Improved RGB Color Space Cylindrical Representation for more info. 
 */

#include <stdio.h>
#include <math.h>
#define pi	3.14159265

void convertBack (double h_deg, double c, double i, double *r, double *g, double *b)
{
	double h_rad; //hue in radians
	h_rad = h_deg * pi / 180;
	*r = i + 2 * c * cos (h_rad) / 3;
	*g = i + 2 * c * cos (h_rad - 2 * pi / 3) / 3;
	*b = i + 2 * c * cos (h_rad - 4 * pi / 3) / 3;
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
		
		convertBack (h, c, i, &r, &g, &b);
		printf ("Red\t= %f, \nGreen\t= %f, \nBlue\t= %f. \n", r, g, b);
		
		if (h < 0 || c < 0 || i < 0 || h > 360 || c > 1 || i > 1)
			printf ("Warning: One or more values are out of range. The result may be erroneous. \n");
	}
}

void instruct (void)
{
	printf ("This program converts an entry in an Improved HCI color space to the corresponding RGB representation. \n"
			"You will be asked to enter the values for hue, chroma and intensity, respectively. \n"
			"The hue should be in degrees, between 0 and 360. The other two should be between 0 and 1. \n"
			"Note: In case the hue is undefined, enter any value for hue and 0 for chroma. \n"
			"All of them should be separated with a space. Enter -1 -1 -1 to exit. \n\n");
}

