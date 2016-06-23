#include <assert.h>
#include "tests.h"
#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"
#include "gmxcpp/Trajectory.h"

int main()
{
    Trajectory t1("tests/test.xtc");
cout << "test" << endl;
    t1.read();
cout << "test" << endl;

    assert(test_equal(t1.GetNAtoms(), 4050));
    assert(test_equal(t1.GetNFrames(), 1001));
    assert(test_equal(t1.GetTime(0), 0.0));
    assert(test_equal(t1.GetTime(1), 2.0));
    assert(test_equal(t1.GetTime(1000), 2000.0));
    assert(test_equal(t1.GetStep(0), 0));
    assert(test_equal(t1.GetStep(1), 1000));
    assert(test_equal(t1.GetStep(1000), 1000000));

    coordinates tc1 = t1.GetXYZ(0, 0);
    coordinates tc2 = t1.GetXYZ(500, 2025);
    coordinates tc3 = t1.GetXYZ(1000, 4049);

    triclinicbox tb1 = t1.GetBox(0);
    triclinicbox tb2 = t1.GetBox(500);
    triclinicbox tb3 = t1.GetBox(1000);

    assert(test_equal(tc1[X], 1.635));
    assert(test_equal(tc1[Y], 2.921));
    assert(test_equal(tc1[Z], 3.370));

    assert(test_equal(tc2[X], 2.350));
    assert(test_equal(tc2[Y], 2.473));
    assert(test_equal(tc2[Z], 1.098));

    assert(test_equal(tc3[X], 1.035));
    assert(test_equal(tc3[Y], 1.206));
    assert(test_equal(tc3[Z], 1.402));

    assert(test_equal(tb1(X,X), 4.0));
    assert(test_equal(tb1(X,Y), 0.0));
    assert(test_equal(tb1(X,Z), 0.0));
    assert(test_equal(tb1(Y,X), 0.0));
    assert(test_equal(tb1(Y,Y), 4.0));
    assert(test_equal(tb1(Y,Z), 0.0));
    assert(test_equal(tb1(Z,X), 0.0));
    assert(test_equal(tb1(Z,Y), 0.0));
    assert(test_equal(tb1(Z,Z), 4.0));

    assert(test_equal(t1.GetBoxVolume(0), 64.0));

    assert(test_equal(tb2(X,X), 3.11876));
    assert(test_equal(tb2(X,Y), 0.0));
    assert(test_equal(tb2(X,Z), 0.0));
    assert(test_equal(tb2(Y,X), 0.0));
    assert(test_equal(tb2(Y,Y), 3.11876));
    assert(test_equal(tb2(Y,Z), 0.0));
    assert(test_equal(tb2(Z,X), 0.0));
    assert(test_equal(tb2(Z,Y), 0.0));
    assert(test_equal(tb2(Z,Z), 3.11876));

    assert(test_equal(tb3(X,X), 3.14139));
    assert(test_equal(tb3(X,Y), 0.0));
    assert(test_equal(tb3(X,Z), 0.0));
    assert(test_equal(tb3(Y,X), 0.0));
    assert(test_equal(tb3(Y,Y), 3.14139));
    assert(test_equal(tb3(Y,Z), 0.0));
    assert(test_equal(tb3(Z,X), 0.0));
    assert(test_equal(tb3(Z,Y), 0.0));
    assert(test_equal(tb3(Z,Z), 3.14139));

    Index index("tests/test.ndx");
    t1 = Trajectory("tests/test.xtc",index);
    t1.read();
    assert(test_equal(t1.GetNAtoms("System"), 4050));
    assert(test_equal(t1.GetNAtoms("C"), 10));
    assert(test_equal(t1.GetNAtoms("SOL"), 4000));

    coordinates tc4 = t1.GetXYZ(0, "C", 0);
    coordinates tc5 = t1.GetXYZ(250, "OW", 500);
    coordinates tc6 = t1.GetXYZ(500, "C", 9);
    coordinates tc7 = t1.GetXYZ(1000, "OW", 999);

    assert(test_equal(tc4[X], 1.635));
    assert(test_equal(tc4[Y], 2.921));
    assert(test_equal(tc4[Z], 3.370));

    assert(test_equal(tc5[X], 2.252));
    assert(test_equal(tc5[Y], 1.456));
    assert(test_equal(tc5[Z], 0.893));

    assert(test_equal(tc6[X], 1.111));
    assert(test_equal(tc6[Y], 0.966));
    assert(test_equal(tc6[Z], 1.541));

    assert(test_equal(tc7[X], 1.040));
    assert(test_equal(tc7[Y], 1.206));
    assert(test_equal(tc7[Z], 1.413));

    Trajectory t3("tests/test.xtc", index);
    t3.read(1000, 1, 1001);
    coordinates tc8 = t3.GetXYZ(0, "OW", 999);
    assert(test_equal(tc8[X], 1.040));
    assert(test_equal(tc8[Y], 1.206));
    assert(test_equal(tc8[Z], 1.413));

    Trajectory t4("tests/test.xtc", index);
    t4.read(0, 5, 1001);
    coordinates tc9 = t4.GetXYZ(200, "OW", 999);
    assert(test_equal(tc9[X], 1.040));
    assert(test_equal(tc9[Y], 1.206));
    assert(test_equal(tc9[Z], 1.413));

    Trajectory t5("tests/test.xtc", index);
    t5.read(0, 5);
    coordinates tc10 = t5.GetXYZ(200, "OW", 999);
    assert(test_equal(tc10[X], 1.040));
    assert(test_equal(tc10[Y], 1.206));
    assert(test_equal(tc10[Z], 1.413));

}
