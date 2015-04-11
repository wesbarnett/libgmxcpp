#include <assert.h>
#include "tests.h"
#include "gmxcpp/Topology.h"

int main()
{
    Index ndx("tests/test.ndx");
    Topology t1("tests/test.tpr",ndx);

    assert(test_equal(t1.GetCharge(0),-2.40000e-01));
    assert(test_equal(t1.GetCharge(99),0.52422));
    assert(test_equal(t1.GetCharge(3,"SOL"),-1.04844));

    assert(test_equal(t1.GetMass(0),1.20110e+01));
    assert(test_equal(t1.GetMass(99),1.008));
    assert(test_equal(t1.GetMass(3,"SOL"),0.00000));

    return 0;
}
