//
// Created by rinsler on 29.10.17.
//

#include <math.h>

#include "../headers/triangle.h"


int is_triangle(double a, double b, double c)
{
    return a + b > c && a + c > b && b + c > a;
}

void get_angle(double a, double b, double c, int *degrees, int *minutes, int *seconds)
{
    double ang = acos((a * a + b * b - c * c) / (2 * a * b)) * M_1_PI * 180;
    *degrees = (int) ang;
    *minutes = (int) ((ang - *degrees) * 60);
    *seconds = (int) round(((ang - *degrees) * 60 - *minutes) * 60);
}
