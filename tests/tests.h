
#include <math.h>

double const TOL = pow(10,-5);

bool test_equal(double a, double b)
{
    bool test = (a >= b-TOL && a <= b+TOL);
    return test;
}
