/* Copyright 2018 Flora Canou, Alexander Zheng | V. C0-C1 (1.0.1) | RGB to Improved HCI Convertor
 * This Source Code Form is licensed under the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, you can obtain one at https://mozilla.org/MPL/2.0/. 
 * The program converts an entry in an RGB color space to the corresponding Improved HCI representation. 
 * See Improved RGB Color Space Cylindrical Representation for more info. 
 */

#include <stdio.h>
#include <math.h>
#define pi	3.14159265

double findHue (double r, double g, double b, double c)
{
	double h_rad, h_deg; //hue in radians, hue in degrees
	if (r == g && g == b) //gray, hue is undefined
	{
		return -1;
	}
	else
	{
		if (g > b)
			h_rad = acos ((2 * r - g - b) / (2 * c));
		else if (g < b)
			h_rad = 2 * pi - acos ((2 * r - g - b) / (2 * c));
		else //g == b has to be given saparately, otherwise producing error
			h_rad = 0;
		h_deg = h_rad * 180 / pi;
		return (h_deg);
	}
}

void convertForth (double r, double g, double b, double *i, double *c, double *h)
{
	double d; //deviation
	*i = (r + g + b) / 3;
	d = sqrt (((r - g)*(r - g) + (g - b)*(g - b) + (b - r)*(b - r)) / 3);
	*c = d * sqrt (6) / 2;
	*h = findHue (r, g, b, *c);
}

void instruct (void);
int main (void)
{
	instruct();
	double r, g, b; //red, green, blue
	double i, c, h; //intensity, chroma, hue in degrees
	
	while (1)
	{
		printf ("Please enter the values. > ");
		scanf ("%lf %lf %lf", &r, &g, &b);
		if (r == -1 && g == -1 && b == -1)
			return 0;
		
		convertForth (r, g, b, &i, &c, &h);
		if (h == -1)
			printf ("Intensity\t= %f, \nChroma\t\t= %f, \nHue is undefined. \n", i, c);
		else
			printf ("Intensity\t= %f, \nChroma\t\t= %f, \nHue\t\t= %f degrees. \n", i, c, h);
		
		if (r < 0 || g < 0 || b < 0 || r > 1 || g > 1 || b > 1)
			printf ("Warning: One or more values are out of range. The result may be erroneous. \n");
	}
}

void instruct (void)
{
	printf ("This program converts an entry in an RGB color space to the corresponding Improved HCI representation. \n"
			"You will be asked to enter the values for red, green and blue, respectively. \n"
			"They should be between 0 and 1 and be separated with a space. \n"
			"Enter -1 -1 -1 to exit. \n\n");
}

