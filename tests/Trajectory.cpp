#include <assert.h>
#include "tests.h"
#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"
#include "gmxcpp/Trajectory.h"

int main()
{
    Trajectory t1("tests/test.xtc");

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

    assert(test_equal(tc1.at(X), 1.635));
    assert(test_equal(tc1.at(Y), 2.921));
    assert(test_equal(tc1.at(Z), 3.370));

    assert(test_equal(tc2.at(X), 2.350));
    assert(test_equal(tc2.at(Y), 2.473));
    assert(test_equal(tc2.at(Z), 1.098));

    assert(test_equal(tc3.at(X), 1.035));
    assert(test_equal(tc3.at(Y), 1.206));
    assert(test_equal(tc3.at(Z), 1.402));

    assert(test_equal(tb1.at(X).at(X), 4.0));
    assert(test_equal(tb1.at(X).at(Y), 0.0));
    assert(test_equal(tb1.at(X).at(Z), 0.0));
    assert(test_equal(tb1.at(Y).at(X), 0.0));
    assert(test_equal(tb1.at(Y).at(Y), 4.0));
    assert(test_equal(tb1.at(Y).at(Z), 0.0));
    assert(test_equal(tb1.at(Z).at(X), 0.0));
    assert(test_equal(tb1.at(Z).at(Y), 0.0));
    assert(test_equal(tb1.at(Z).at(Z), 4.0));

    assert(test_equal(t1.GetBoxVolume(0), 64.0));

    assert(test_equal(tb2.at(X).at(X), 3.11876));
    assert(test_equal(tb2.at(X).at(Y), 0.0));
    assert(test_equal(tb2.at(X).at(Z), 0.0));
    assert(test_equal(tb2.at(Y).at(X), 0.0));
    assert(test_equal(tb2.at(Y).at(Y), 3.11876));
    assert(test_equal(tb2.at(Y).at(Z), 0.0));
    assert(test_equal(tb2.at(Z).at(X), 0.0));
    assert(test_equal(tb2.at(Z).at(Y), 0.0));
    assert(test_equal(tb2.at(Z).at(Z), 3.11876));

    assert(test_equal(tb3.at(X).at(X), 3.14139));
    assert(test_equal(tb3.at(X).at(Y), 0.0));
    assert(test_equal(tb3.at(X).at(Z), 0.0));
    assert(test_equal(tb3.at(Y).at(X), 0.0));
    assert(test_equal(tb3.at(Y).at(Y), 3.14139));
    assert(test_equal(tb3.at(Y).at(Z), 0.0));
    assert(test_equal(tb3.at(Z).at(X), 0.0));
    assert(test_equal(tb3.at(Z).at(Y), 0.0));
    assert(test_equal(tb3.at(Z).at(Z), 3.14139));

    Index index("tests/test.ndx");
    Trajectory t2("tests/test.xtc",index);
    assert(test_equal(t2.GetNAtoms("System"), 4050));
    assert(test_equal(t2.GetNAtoms("C"), 10));
    assert(test_equal(t2.GetNAtoms("SOL"), 4000));

    coordinates tc4 = t2.GetXYZ(0, "C", 0);
    coordinates tc5 = t2.GetXYZ(250, "OW", 500);
    coordinates tc6 = t2.GetXYZ(500, "C", 9);
    coordinates tc7 = t2.GetXYZ(1000, "OW", 999);

    assert(test_equal(tc4.at(X), 1.635));
    assert(test_equal(tc4.at(Y), 2.921));
    assert(test_equal(tc4.at(Z), 3.370));

    assert(test_equal(tc5.at(X), 2.252));
    assert(test_equal(tc5.at(Y), 1.456));
    assert(test_equal(tc5.at(Z), 0.893));

    assert(test_equal(tc6.at(X), 1.111));
    assert(test_equal(tc6.at(Y), 0.966));
    assert(test_equal(tc6.at(Z), 1.541));

    assert(test_equal(tc7.at(X), 1.040));
    assert(test_equal(tc7.at(Y), 1.206));
    assert(test_equal(tc7.at(Z), 1.413));

    Trajectory t3("tests/test.xtc", 10);
    assert(test_equal(t3.GetNFrames(), 10));

    Trajectory t4("tests/test.xtc", "tests/test.ndx", 10);
    assert(test_equal(t4.GetNFrames(), 10));

    vector <coordinates> tc8 = t4.GetXYZ(3,"C");
    assert(test_equal(tc8.at(0).at(X), 0.532));
    assert(test_equal(tc8.at(0).at(Y), 2.833));
    assert(test_equal(tc8.at(0).at(Z), 2.718));
    assert(test_equal(tc8.at(4).at(X), 2.474));
    assert(test_equal(tc8.at(4).at(Y), 1.417));
    assert(test_equal(tc8.at(4).at(Z), 2.398));
    assert(test_equal(tc8.at(9).at(X), 1.095));
    assert(test_equal(tc8.at(9).at(Y), 2.881));
    assert(test_equal(tc8.at(9).at(Z), 1.157));

    // TODO add test for reading in entire frame
}
