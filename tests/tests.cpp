
#include <assert.h>
#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"
#include "gmxcpp/Trajectory.h"
#include "gmxcpp/Utils.h"

double const TOL = pow(10,-5);

bool test_equal(double a, double b)
{
    bool test = (a >= b-TOL && a <= b+TOL);
    return test;
}

int main()
{

    /* Test some basic constants */
    assert(X==0);
    assert(Y==1);
    assert(Z==2);
    assert(DIM==3);

    /* Test coordinates class overloaded operations */
    double x1 = 1.2;
    double y1 = -2.8;
    double z1 = 3.1;

    double x2 = -4.92;
    double y2 = 5.13;
    double z2 = 6.04;

    coordinates c1(x1,y1,z1);
    coordinates c2(x2,y2,z2);
    coordinates c3;
    coordinates c4;

    assert(test_equal(x1,c1.at(X)));
    assert(test_equal(y1,c1.at(Y)));
    assert(test_equal(z1,c1.at(Z)));

    assert(test_equal(x2,c2.at(X)));
    assert(test_equal(y2,c2.at(Y)));
    assert(test_equal(z2,c2.at(Z)));

    c3 = c2 - c1;
    assert(test_equal(x2-x1,c3.at(X)));
    assert(test_equal(y2-y1,c3.at(Y)));
    assert(test_equal(z2-z1,c3.at(Z)));

    c4 = c3;
    c3 -= c2;
    assert(test_equal(c4.at(X)-x2,c3.at(X)));
    assert(test_equal(c4.at(Y)-y2,c3.at(Y)));
    assert(test_equal(c4.at(Z)-z2,c3.at(Z)));

    c3 -= c3;
    assert(test_equal(0.0,c3.at(X)));
    assert(test_equal(0.0,c3.at(Y)));
    assert(test_equal(0.0,c3.at(Z)));

    c3 = c2 + c1;
    assert(test_equal(x2+x1,c3.at(X)));
    assert(test_equal(y2+y1,c3.at(Y)));
    assert(test_equal(z2+z1,c3.at(Z)));

    c4 = c3;
    c3 += c1;
    assert(test_equal(c4.at(X)+x1,c3.at(X)));
    assert(test_equal(c4.at(Y)+y1,c3.at(Y)));
    assert(test_equal(c4.at(Z)+z1,c3.at(Z)));

    c3 = c2 / 5.8;
    assert(test_equal(x2/5.8,c3.at(X)));
    assert(test_equal(y2/5.8,c3.at(Y)));
    assert(test_equal(z2/5.8,c3.at(Z)));

    c4 = c3;
    c3 /= 3.14;
    assert(test_equal(c4.at(X)/3.14,c3.at(X)));
    assert(test_equal(c4.at(Y)/3.14,c3.at(Y)));
    assert(test_equal(c4.at(Z)/3.14,c3.at(Z)));

    c3 = c1 * 1.2;
    assert(test_equal(x1*1.2,c3.at(X)));
    assert(test_equal(y1*1.2,c3.at(Y)));
    assert(test_equal(z1*1.2,c3.at(Z)));
    
    c4 = c3;
    c3 *= 3.14;
    assert(test_equal(c4.at(X)*3.14,c3.at(X)));
    assert(test_equal(c4.at(Y)*3.14,c3.at(Y)));
    assert(test_equal(c4.at(Z)*3.14,c3.at(Z)));

    /* Test triclinicbox and some utils*/
    triclinicbox b1(3.5,4.5,4.0);
    assert(test_equal(b1.at(X).at(X),3.5));
    assert(test_equal(b1.at(X).at(Y),0.0));
    assert(test_equal(b1.at(X).at(Z),0.0));
    assert(test_equal(b1.at(Y).at(X),0.0));
    assert(test_equal(b1.at(Y).at(Y),4.5));
    assert(test_equal(b1.at(Y).at(Z),0.0));
    assert(test_equal(b1.at(Z).at(X),0.0));
    assert(test_equal(b1.at(Z).at(Y),0.0));
    assert(test_equal(b1.at(Z).at(Z),4.0));

    coordinates c6(3.6,4.7,5.0);
    coordinates c7 = pbc(c6,b1);
    assert(test_equal(c7.at(X),0.1));
    assert(test_equal(c7.at(Y),0.2));
    assert(test_equal(c7.at(Z),1.0));

    triclinicbox b2(5.0,0.0,0.0,0.0,5.0,0.0,2.5,2.5,3.5);
    coordinates c8(5.5,5.5,3.5);
    assert(test_equal(b2.at(X).at(X),5.0));
    assert(test_equal(b2.at(X).at(Y),0.0));
    assert(test_equal(b2.at(X).at(Z),0.0));
    assert(test_equal(b2.at(Y).at(X),0.0));
    assert(test_equal(b2.at(Y).at(Y),5.0));
    assert(test_equal(b2.at(Y).at(Z),0.0));
    assert(test_equal(b2.at(Z).at(X),2.5));
    assert(test_equal(b2.at(Z).at(Y),2.5));
    assert(test_equal(b2.at(Z).at(Z),3.5));

    coordinates c9 = pbc(c8,b2);
    assert(test_equal(c9.at(X),-2.0));
    assert(test_equal(c9.at(Y),-2.0));
    assert(test_equal(c9.at(Z),0.0));

    assert(test_equal(dot(c6,c7),6.3));
    assert(test_equal(magnitude(c6),7.749193506));

    assert(test_equal(distance(c8,c9,b2),0.0));
    assert(test_equal(distance(c6,c8,b1),2.33452));

    Trajectory t1("test.xtc");
    assert(test_equal(t1.GetNAtoms(),4050));
    assert(test_equal(t1.GetNFrames(),1001));
    assert(test_equal(t1.GetTime(0),0.0));
    assert(test_equal(t1.GetTime(1),2.0));
    assert(test_equal(t1.GetTime(1000),2000.0));
    assert(test_equal(t1.GetStep(0),0));
    assert(test_equal(t1.GetStep(1),1000));
    assert(test_equal(t1.GetStep(1000),1000000));

    coordinates tc1 = t1.GetXYZ(0,0);
    coordinates tc2 = t1.GetXYZ(500,2025);
    coordinates tc3 = t1.GetXYZ(1000,4049);

    triclinicbox tb1 = t1.GetBox(0);
    triclinicbox tb2 = t1.GetBox(500);
    triclinicbox tb3 = t1.GetBox(1000);

    assert(test_equal(tc1.at(X),1.635));
    assert(test_equal(tc1.at(Y),2.921));
    assert(test_equal(tc1.at(Z),3.370));

    assert(test_equal(tc2.at(X),2.350));
    assert(test_equal(tc2.at(Y),2.473));
    assert(test_equal(tc2.at(Z),1.098));

    assert(test_equal(tc3.at(X),1.035));
    assert(test_equal(tc3.at(Y),1.206));
    assert(test_equal(tc3.at(Z),1.402));

    assert(test_equal(tb1.at(X).at(X),4.0));
    assert(test_equal(tb1.at(X).at(Y),0.0));
    assert(test_equal(tb1.at(X).at(Z),0.0));
    assert(test_equal(tb1.at(Y).at(X),0.0));
    assert(test_equal(tb1.at(Y).at(Y),4.0));
    assert(test_equal(tb1.at(Y).at(Z),0.0));
    assert(test_equal(tb1.at(Z).at(X),0.0));
    assert(test_equal(tb1.at(Z).at(Y),0.0));
    assert(test_equal(tb1.at(Z).at(Z),4.0));

    assert(test_equal(tb2.at(X).at(X),3.11876));
    assert(test_equal(tb2.at(X).at(Y),0.0));
    assert(test_equal(tb2.at(X).at(Z),0.0));
    assert(test_equal(tb2.at(Y).at(X),0.0));
    assert(test_equal(tb2.at(Y).at(Y),3.11876));
    assert(test_equal(tb2.at(Y).at(Z),0.0));
    assert(test_equal(tb2.at(Z).at(X),0.0));
    assert(test_equal(tb2.at(Z).at(Y),0.0));
    assert(test_equal(tb2.at(Z).at(Z),3.11876));

    assert(test_equal(tb3.at(X).at(X),3.14139));
    assert(test_equal(tb3.at(X).at(Y),0.0));
    assert(test_equal(tb3.at(X).at(Z),0.0));
    assert(test_equal(tb3.at(Y).at(X),0.0));
    assert(test_equal(tb3.at(Y).at(Y),3.14139));
    assert(test_equal(tb3.at(Y).at(Z),0.0));
    assert(test_equal(tb3.at(Z).at(X),0.0));
    assert(test_equal(tb3.at(Z).at(Y),0.0));
    assert(test_equal(tb3.at(Z).at(Z),3.14139));

    Trajectory t2("test.xtc","test.ndx");
    assert(test_equal(t2.GetNAtoms("System"),4050));
    assert(test_equal(t2.GetNAtoms("C"),10));
    assert(test_equal(t2.GetNAtoms("SOL"),4000));

    coordinates tc4 = t2.GetXYZ(0,"C",0);
    coordinates tc5 = t2.GetXYZ(250,"OW",500);
    coordinates tc6 = t2.GetXYZ(500,"C",9);
    coordinates tc7 = t2.GetXYZ(1000,"OW",999);

    assert(test_equal(tc4.at(X),1.635));
    assert(test_equal(tc4.at(Y),2.921));
    assert(test_equal(tc4.at(Z),3.370));

    assert(test_equal(tc5.at(X),2.252));
    assert(test_equal(tc5.at(Y),1.456));
    assert(test_equal(tc5.at(Z),0.893));

    assert(test_equal(tc6.at(X),1.111));
    assert(test_equal(tc6.at(Y),0.966));
    assert(test_equal(tc6.at(Z),1.541));

    assert(test_equal(tc7.at(X),1.040));
    assert(test_equal(tc7.at(Y),1.206));
    assert(test_equal(tc7.at(Z),1.413));

    Trajectory t3("test.xtc",10);
    assert(test_equal(t3.GetNFrames(),10));

    Trajectory t4("test.xtc","test.ndx",10);
    assert(test_equal(t4.GetNFrames(),10));

}
