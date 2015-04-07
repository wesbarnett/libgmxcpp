#include <assert.h>
#include "tests.h"
#include "gmxcpp/triclinicbox.h"

int main()
{
    /* Test triclinicbox*/
    triclinicbox b1(3.5, 4.5, 4.0);

    assert(test_equal(b1.at(X).at(X), 3.5));
    assert(test_equal(b1.at(X).at(Y), 0.0));
    assert(test_equal(b1.at(X).at(Z), 0.0));
    assert(test_equal(b1.at(Y).at(X), 0.0));
    assert(test_equal(b1.at(Y).at(Y), 4.5));
    assert(test_equal(b1.at(Y).at(Z), 0.0));
    assert(test_equal(b1.at(Z).at(X), 0.0));
    assert(test_equal(b1.at(Z).at(Y), 0.0));
    assert(test_equal(b1.at(Z).at(Z), 4.0));

    triclinicbox b2(5.0, 0.0, 0.0, 0.0, 5.0, 0.0, 2.5, 2.5, 3.5);
    assert(test_equal(b2.at(X).at(X), 5.0));
    assert(test_equal(b2.at(X).at(Y), 0.0));
    assert(test_equal(b2.at(X).at(Z), 0.0));
    assert(test_equal(b2.at(Y).at(X), 0.0));
    assert(test_equal(b2.at(Y).at(Y), 5.0));
    assert(test_equal(b2.at(Y).at(Z), 0.0));
    assert(test_equal(b2.at(Z).at(X), 2.5));
    assert(test_equal(b2.at(Z).at(Y), 2.5));
    assert(test_equal(b2.at(Z).at(Z), 3.5));

    return 0;
}
