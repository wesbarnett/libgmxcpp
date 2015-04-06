
#include <assert.h>
#include "tests.h"
#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"
#include "gmxcpp/Utils.h"

int main() 
{

    /* Test some utils*/
    triclinicbox b1(3.5,4.5,4.0);

    coordinates c6(3.6,4.7,5.0);
    coordinates c7 = pbc(c6,b1);
    assert(test_equal(c7.at(X),0.1));
    assert(test_equal(c7.at(Y),0.2));
    assert(test_equal(c7.at(Z),1.0));

    triclinicbox b2(5.0,0.0,0.0,0.0,5.0,0.0,2.5,2.5,3.5);
    coordinates c8(5.5,5.5,3.5);

    coordinates c9 = pbc(c8,b2);
    assert(test_equal(c9.at(X),-2.0));
    assert(test_equal(c9.at(Y),-2.0));
    assert(test_equal(c9.at(Z),0.0));

    assert(test_equal(dot(c6,c7),6.3));
    assert(test_equal(magnitude(c6),7.749193506));

    assert(test_equal(distance(c8,c9,b2),0.0));
    assert(test_equal(distance(c6,c8,b1),2.33452));

	return 0;
}
