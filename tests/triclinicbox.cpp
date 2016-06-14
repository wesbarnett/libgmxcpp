#include <assert.h>
#include "tests.h"
#include "gmxcpp/triclinicbox.h"

int main()
{
    /* Test triclinicbox*/
    triclinicbox b1(3.5, 4.5, 4.0);

    assert(test_equal(b1(X,X), 3.5));
    assert(test_equal(b1(X,Y), 0.0));
    assert(test_equal(b1(X,Z), 0.0));
    assert(test_equal(b1(Y,X), 0.0));
    assert(test_equal(b1(Y,Y), 4.5));
    assert(test_equal(b1(Y,Z), 0.0));
    assert(test_equal(b1(Z,X), 0.0));
    assert(test_equal(b1(Z,Y), 0.0));
    assert(test_equal(b1(Z,Z), 4.0));

    triclinicbox b2(5.0, 0.0, 0.0, 0.0, 5.0, 0.0, 2.5, 2.5, 3.5);
    assert(test_equal(b2(X,X), 5.0));
    assert(test_equal(b2(X,Y), 0.0));
    assert(test_equal(b2(X,Z), 0.0));
    assert(test_equal(b2(Y,X), 0.0));
    assert(test_equal(b2(Y,Y), 5.0));
    assert(test_equal(b2(Y,Z), 0.0));
    assert(test_equal(b2(Z,X), 2.5));
    assert(test_equal(b2(Z,Y), 2.5));
    assert(test_equal(b2(Z,Z), 3.5));

    return 0;
}
