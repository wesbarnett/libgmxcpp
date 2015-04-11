#include <assert.h>
#include "tests.h"
#include "gmxcpp/Topology.h"

#include <iostream>
using namespace std;


int main()
{
    Topology t1("tests/test.tpr");

    cout << t1.GetQ(0) << endl;

}
