#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265
#define _CRT_NO_WARNINGS
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
	double gradus = angle * 180 / M_PI;
	int grad = (int)gradus;
	int minutes = (int)((gradus - grad) * 60);
	int second = (int)(((gradus - grad) * 60 - minutes) * 60);
	result->degrees = grad;
	result->minutes = minutes;
	result->seconds = second;
}

void printRes(DMS *angle)
{
	printf("Deg:%d, Min:%d, Sec:%d\n", angle->degrees, angle->minutes, angle->seconds);
}

int main()
{
	double a, b, c;
	char buf[80];
	do
	{
		printf("Enter triangle sides ");
		gets(buf);
		int count = sscanf_s(buf, "%lf%lf%lf", &a, &b, &c);
		if (count == 3) break;
	}while (1);

	if (correct(a, b, c))
	{
		double p = (a + b + c) / 2;
		double s = sqrt(p * (p - a) * (p - b) * (p - c));
		double firstAngle = asin(2 * s / a / b);
		double secondAngle = asin(2 * s / c / b);
		double thirdAngle = asin(2 * s / a / c);
		DMS a1, a2, a3;
		calc(firstAngle, &a1);
		calc(secondAngle, &a2);
		calc(thirdAngle, &a3);
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
