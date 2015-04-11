#include <assert.h>
#include "tests.h"
#include "gmxcpp/Topology.h"

int main()
{
    Index ndx("tests/test.ndx");
    Topology top("tests/test.tpr",ndx);

    assert(test_equal(top.GetCharge(0),-2.40000e-01));
    assert(test_equal(top.GetCharge(99),0.52422));
    assert(test_equal(top.GetCharge(3,"SOL"),-1.04844));

    assert(test_equal(top.GetMass(0),1.20110e+01));
    assert(test_equal(top.GetMass(99),1.008));
    assert(test_equal(top.GetMass(3,"SOL"),0.00000));

    assert(test_equal(top.GetMass("C").at(2),12.011));
    assert(test_equal(top.GetMass("OW").at(0),16.0));
    assert(test_equal(top.GetCharge("C").at(2),-0.24));
    assert(test_equal(top.GetCharge("OW").at(0),0.0));

    return 0;
}
