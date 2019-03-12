/* Copyright 2018-2019 Flora Canou, Alexander Zheng | V. C5-1.3.0 | Improved HCI to RGB Convertor
 * This Source Code Form is licensed under the Mozilla Public License, v. 2.0. 
 * If you have not received a copy of the license, visit https://mozilla.org/MPL/2.0/. 
 * This program converts entries between Improved HCI and RGB color models. 
 * See Improved HCI Color Model Specifications for more info. 
 */

#include <stdio.h>
#include <math.h>
#define TAU	6.28318530718 //2*PI

double ihciForth_hue (double p1, double p2, double p3, double C)
{
	double H; //hue
	if (p1 == p2 && p2 == p3)
		return -1; //gray, hue is undefined
	else if (p2 >= p3)
		H = acos ((2*p1 - p2 - p3) / (2*C));
	else
		H = TAU - acos ((2*p1 - p2 - p3) / (2*C));
	return (H);
}

void ihciForth (double p1, double p2, double p3, double *H, double *C, double *I)
{
	*C = sqrt (((p1 - p2)*(p1 - p2) + (p2 - p3)*(p2 - p3) + (p3 - p1)*(p3 - p1)) / 2);
	*H = ihciForth_hue (p1, p2, p3, *C);
	*I = (p1 + p2 + p3) / 3;
}

void ihciBack (double H, double C, double I, double *p1, double *p2, double *p3)
{
	*p1 = I + 2*C * cos (H) / 3;
	*p2 = I + 2*C * cos (H - TAU / 3) / 3;
	*p3 = I + 2*C * cos (H + TAU / 3) / 3;
}

void instruct (void);
int main (void)
{
	instruct();
	int mode = 0;
	double order[3];
	double H, C, I; //hue in degrees, intensity, chroma
	double r, g, b; //red, green, blue
	
	while (1)
	{
		if (mode)
			printf ("Mode: forward (RGB to IHCI). \n");
		else
			printf ("Mode: backward (IHCI to RGB). \n");
		printf ("> ");
		scanf ("%lf %lf %lf", &order[0], &order[1], &order[2]);
		if (order[0] == -1)
		{
			if (order[1] == 0 && order[2] == 0)
			{
				mode = (mode + 1) % 2;
				continue;
			}
			if (order[1] == -1 && order[2] == -1)
				return 0;
		}
		if (mode) //RGB to IHCI
		{
			r = order[0]; g = order[1]; b = order[2];
			ihciForth (r, g, b, &H, &C, &I);
			if (H == -1)
				printf ("Hue is undefined, \nChroma\t\t= %f, \nIntensity\t= %f. \n", C, I);
			else
				printf ("Hue\t\t= %f degrees, \nChroma\t\t= %f, \nIntensity\t= %f. \n", H*360 / TAU, C, I);
		}
		else //IHCI to RGB
		{
			H = order[0]*TAU / 360; //degree to radian
			C = order[1]; I = order[2];
			ihciBack (H, C, I, &r, &g, &b);
			printf ("Red\t= %f, \nGreen\t= %f, \nBlue\t= %f. \n", r, g, b);
		}
	}
}

void instruct (void)
{
	printf ("This program converts entries between Improved HCI and RGB color models. \n"
		"In forward mode, enter the values for red, green and blue, respectively. \n"
		"They should be between 0 and 1. \n"
		"In backward mode, enter the values for hue, chroma and intensity, respectively. \n"
		"The hue should be in degrees, between 0 and 360. The other two should be between 0 and 1. \n"
		"In case the hue is undefined, enter any value for hue and 0 for chroma. \n"
		"The entries should be separated with a space. \n"
		"Enter -1 0 0 to toggle modes. Enter -1 -1 -1 to exit. \n\n");
}
