
#include <cmath>
#include <math.h>
#include <iostream>

double const TOL = pow(10,-5);

bool test_equal(double a, double b)
{
    std::cout << abs(a-b) << std::endl;
    bool test = (std::abs(a-b) <= TOL);
    std::cout << test << std::endl;
    return test;
}
