//
// Created by rinsler on 29.10.17.
//

#include <math.h>

#include "../headers/triangle.h"


int is_triangle(double a, double b, double c)
{
    return a + b > c && a + c > b && b + c > a;
}

double get_angle_in_degrees(double a, double b, double c)
{
    return acos((a * a + b * b - c * c) / (2 * a * b)) * M_1_PI * 180;
}
