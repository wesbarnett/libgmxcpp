#include <assert.h>
#include "tests.h"
#include "gmxcpp/coordinates.h"

int main()
{
    /* Test some basic constants */
    assert(X == 0);
    assert(Y == 1);
    assert(Z == 2);
    assert(DIM == 3);

    /* Test coordinates class overloaded operations */
    double x1 = 1.2;
    double y1 = -2.8;
    double z1 = 3.1;

    double x2 = -4.92;
    double y2 = 5.13;
    double z2 = 6.04;

    coordinates c1(x1, y1, z1);
    coordinates c2(x2, y2, z2);
    coordinates c3;
    coordinates c4;

    assert(test_equal(x1, c1.at(X)));
    assert(test_equal(y1, c1.at(Y)));
    assert(test_equal(z1, c1.at(Z)));

    assert(test_equal(x2, c2.at(X)));
    assert(test_equal(y2, c2.at(Y)));
    assert(test_equal(z2, c2.at(Z)));

    c3 = c2 - c1;
    assert(test_equal(x2 - x1, c3.at(X)));
    assert(test_equal(y2 - y1, c3.at(Y)));
    assert(test_equal(z2 - z1, c3.at(Z)));

    c4 = c3;
    c3 -= c2;
    assert(test_equal(c4.at(X) - x2, c3.at(X)));
    assert(test_equal(c4.at(Y) - y2, c3.at(Y)));
    assert(test_equal(c4.at(Z) - z2, c3.at(Z)));

    c3 -= c3;
    assert(test_equal(0.0, c3.at(X)));
    assert(test_equal(0.0, c3.at(Y)));
    assert(test_equal(0.0, c3.at(Z)));

    c3 = c2 + c1;
    assert(test_equal(x2 + x1, c3.at(X)));
    assert(test_equal(y2 + y1, c3.at(Y)));
    assert(test_equal(z2 + z1, c3.at(Z)));

    c4 = c3;
    c3 += c1;
    assert(test_equal(c4.at(X) + x1, c3.at(X)));
    assert(test_equal(c4.at(Y) + y1, c3.at(Y)));
    assert(test_equal(c4.at(Z) + z1, c3.at(Z)));

    c3 = c2 / 5.8;
    assert(test_equal(x2 / 5.8, c3.at(X)));
    assert(test_equal(y2 / 5.8, c3.at(Y)));
    assert(test_equal(z2 / 5.8, c3.at(Z)));

    c4 = c3;
    c3 /= 3.14;
    assert(test_equal(c4.at(X) / 3.14, c3.at(X)));
    assert(test_equal(c4.at(Y) / 3.14, c3.at(Y)));
    assert(test_equal(c4.at(Z) / 3.14, c3.at(Z)));

    c3 = c1 * 1.2;
    assert(test_equal(x1 * 1.2, c3.at(X)));
    assert(test_equal(y1 * 1.2, c3.at(Y)));
    assert(test_equal(z1 * 1.2, c3.at(Z)));

    c3 = 1.2 * c1;
    assert(test_equal(x1 * 1.2, c3.at(X)));
    assert(test_equal(y1 * 1.2, c3.at(Y)));
    assert(test_equal(z1 * 1.2, c3.at(Z)));

    c4 = c3;
    c3 *= 3.14;
    assert(test_equal(c4.at(X) * 3.14, c3.at(X)));
    assert(test_equal(c4.at(Y) * 3.14, c3.at(Y)));
    assert(test_equal(c4.at(Z) * 3.14, c3.at(Z)));

    return 0;
}
