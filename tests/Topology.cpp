#include <assert.h>
#include "tests.h"
#include "gmxcpp/Topology.h"

#include <iostream>
using namespace std;


int main()
{
    //TODO: Add more tests for charges with index groups.
    //TODO: Add tests for masses
    Index ndx("tests/test.ndx");
    Topology t1("tests/test.tpr",ndx);

    assert(test_equal(t1.GetCharge(0),-2.40000e-01));
    assert(test_equal(t1.GetCharge(99),0.52422));

    return 0;
}
