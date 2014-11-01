
#include <iostream>
#include <string>
#include "Trajectory.h"
#include "CommandLine.h"
using namespace std;

int main(int argc, char* argv[]) {

	string xtcfile;
    if(!getArgument(argc,argv,"-f",&xtcfile)) return -1;

    string ndxfile;
    if(!getArgument(argc,argv,"-n",&ndxfile)) return -1;

	Trajectory traj(xtcfile,ndxfile);

    rvec xyz;
    matrix box;

    cout << "Printing all coordinates from C group for frame 0: " << endl;
    for (int i=0;i<traj.GetNAtoms("C");i++) {
        traj.GetXYZ(0,"C",i,xyz);
        cout << xyz[X] << " " << xyz[Y] << " " << xyz[Z] << endl;
    }

    cout << "Box size for frame 0: " << endl;
    traj.GetBox(0,box);
    for (int j=0; j<3; j++) {
        for (int k=0; k<3; k++) {
            cout << box[j][k] << " ";
        }
        cout << endl;
    }

    return 0;
}
