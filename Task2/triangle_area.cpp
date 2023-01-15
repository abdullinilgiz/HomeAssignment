#include "triangle_area.h"

double triangle_area (double a, double b, double c)
{
    if (a <= 0. || b <= 0. || c <= 0.) {
        return 0.;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0.;
    }
    double p = (a + b + c) / 2.;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
}
