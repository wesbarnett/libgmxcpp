
#include <iostream>
#include <string>
#include "Trajectory.h"
#include "CommandLine.h"
using namespace std;

int main(int argc, char* argv[]) {

    const string group = "C";
    const int first = 0;
    const int last = 5;

	string xtcfile;
    if(!getArgument(argc,argv,"-f",&xtcfile)) return -1;

    string ndxfile;
    if(!getArgument(argc,argv,"-n",&ndxfile)) return -1;

	Trajectory traj(xtcfile,ndxfile);

    rvec xyz;
    matrix box;

    for (int frame=first; frame<=last; frame++) {
        cout << endl;
        cout << "Time: " << traj.GetTime(frame) << endl;
        cout << "Step: " << traj.GetStep(frame) << endl;
        cout << endl;

        cout << "Coordinates for group " << group << ":" << endl;
        for (int i=0;i<traj.GetNAtoms(group);i++) {
            traj.GetXYZ(frame,group,i,xyz);
            cout << xyz[X] << " " << xyz[Y] << " " << xyz[Z] << endl;
        }
        cout << endl;

        cout << "Box: " << endl;
        traj.GetBox(frame,box);
        for (int j=0; j<DIM; j++) {
            for (int k=0; k<DIM; k++) {
                cout << box[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
