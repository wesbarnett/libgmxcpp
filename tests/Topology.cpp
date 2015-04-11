#include <assert.h>
#include "tests.h"
#include "gmxcpp/Topology.h"

#include <iostream>
using namespace std;


int main()
{
    Topology t1("tests/test.tpr");

    //TODO
    cout << t1.GetCharge(0) << endl;

}
