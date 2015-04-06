
#include <cmath>
#include <math.h>
#include <iostream>

double const TOL = pow(10,-5);

bool test_equal(double a, double b)
{
    bool test = (std::abs(a-b) <= TOL);
    return test;
}
