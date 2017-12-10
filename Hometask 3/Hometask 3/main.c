#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _DMS
{
	int degrees, minutes, seconds;
} DMS;

int correct(double a, double b, double c);
void calc(double angle, DMS *result);
void printRes(DMS *angle);

int correct(double a, double b, double c)
{
	return a + b > c && a + c > b && b + c > a;
}

void calc(double angle, DMS *result)
{
	double grad = angle * 180 / 3.14159265;
	int gr = (int)grad;
	int min = (int)((grad - gr) * 60);
	int sec = (int)(((grad - gr) * 60 - min) * 60);
	result->degrees = gr;
	result->minutes = min;
	result->seconds = sec;
}

void printRes(DMS *angle)
{
	printf("Deg:%d, Min:%d, Sec:%d\n", angle->degrees, angle->minutes, angle->seconds);
}

int main()
{
	double a, b, c;
	do {
		printf("Enter triangle sides ");
		int count = scanf_s("%lf%lf%lf", &a, &b, &c);
		if (count == 3) break;
	} while (1);

	if (correct(a, b, c))
	{
		double p = (a + b + c) / 2;
		double s = sqrt(p * (p - a) * (p - b) * (p - c));
		double angle1 = asin(2 * s / a / b);
		double angle2 = asin(2 * s / c / b);
		double angle3 = asin(2 * s / a / c);
		DMS a1, a2, a3;
		calc(angle1, &a1);
		calc(angle2, &a2);
		calc(angle3, &a3);
		printRes(&a1);
		printRes(&a2);
		printRes(&a3);
	}
	else
	{
		printf("No triangle may be built\n");
	}
	system("pause");
	return 0;
}
