/* Copyright 2018 Flora Canou, Alexander Zheng | V. C4-1.2.0 | RGB to Improved HCI Convertor
 * This Source Code Form is licensed under the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, you can obtain one at https://mozilla.org/MPL/2.0/. 
 * The program converts an entry in an RGB color model to the corresponding Improved HCI representation. 
 * See Improved HCI Color Model Specifications for more info. 
 */

#include <stdio.h>
#include <math.h>
#define pi	3.14159265359

double ihciForth_hue (double p1, double p2, double p3, double C)
{
	double H; //hue
	if (p1 == p2 && p2 == p3)
		return -1; //gray, hue is undefined
	else if (p2 >= p3)
		H = acos ((2*p1 - p2 - p3) / (2*C));
	else
		H = 2*pi - acos ((2*p1 - p2 - p3) / (2*C));
	return (H);
}

void ihciForth (double p1, double p2, double p3, double *H, double *C, double *I)
{
	*C = sqrt (((p1 - p2)*(p1 - p2) + (p2 - p3)*(p2 - p3) + (p3 - p1)*(p3 - p1)) / 2);
	*H = ihciForth_hue (p1, p2, p3, *C);
	*I = (p1 + p2 + p3) / 3;
}

void instruct (void);
int main (void)
{
	instruct();
	double r, g, b; //red, green, blue
	double H, C, I; //hue in degrees, intensity, chroma
	
	while (1)
	{
		printf ("Please enter the values. > ");
		scanf ("%lf %lf %lf", &r, &g, &b);
		if (r == -1 && g == -1 && b == -1)
			return 0;
		else if (r < 0 || g < 0 || b < 0 || r > 1 || g > 1 || b > 1)
			printf ("Warning: One or more values are out of range. The result may be erroneous. \n");
		
		ihciForth (r, g, b, &H, &C, &I);
		if (H == -1)
			printf ("Hue is undefined, \nChroma\t\t= %f, \nIntensity\t= %f. \n", C, I);
		else
		{
			H = H*180 / pi; //radian to degree
			printf ("Hue\t\t= %f degrees, \nChroma\t\t= %f, \nIntensity\t= %f. \n", H, C, I);
		}
	}
}

void instruct (void)
{
	printf ("This program converts an entry in an RGB color model to the corresponding Improved HCI representation. \n"
			"You will be asked to enter the values for red, green and blue, respectively. \n"
			"They should be between 0 and 1 and be separated with a space. \n"
			"Enter -1 -1 -1 to exit. \n\n");
}

