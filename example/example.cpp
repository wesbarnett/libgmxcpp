
#include <iostream>
#include <string>
#include "Utils.h"
#include "Trajectory.h"
#include "CommandLine.h"
using namespace std;

bool parseCommandLine(int argc,char* argv[],string *xtcfile,string *ndxfile);
void print(Trajectory *traj, int first, int last, string group);
void printUsage(string program);

// Parses the command line, then prints data to standard out
int main(int argc, char* argv[]) {

    const string group = "C";
    const int first = 0;
    const int last = 5;
    string xtcfile, ndxfile;

    if (!parseCommandLine(argc,argv,&xtcfile,&ndxfile)) return -1;

    Trajectory *traj = new Trajectory(xtcfile,ndxfile);

    //print(traj,first,last,group);

    return 0;
}

// Parses the command line, getting the xtc file and index file names. Also
// checks if help flag is initiated.
bool parseCommandLine(int argc,char* argv[],string *xtcfile,string *ndxfile) {

	if(checkHelpArg(argc,argv,"-h")) {
        printUsage(argv[0]);
        return false;
	}

    if(!getArgument(argc,argv,"-f",xtcfile)) {
        printUsage(argv[0]);
        return false;
    }

    if(!getArgument(argc,argv,"-n",ndxfile)) {
        printUsage(argv[0]);
        return false;
    }
    
    if (!fileExists(*xtcfile)) {
        cout << "ERROR: " << *xtcfile << " does not exist." << endl;
        return false;
    }

    if (!fileExists(*ndxfile)) {
        cout << "ERROR: " << *ndxfile << " does not exist." << endl;
        return false;
    }
    
    return true;
}

void printUsage(string program) {
    cout << endl;
	cout << "Usage:" << endl;
	cout << "  " << program << " -f traj.xtc -n index.ndx" << endl;
    cout << "Arguments:" << endl;
	cout << "   traj.xtc  (Input, Gromacs xtc file)" << endl;
	cout << "   index.ndx (Input, Gromacs index file)" << endl;
	cout << endl;
    return;
}

void print(Trajectory *traj,int first, int last, string group) {

    rvec xyz;
    matrix box;

    cout << fixed << setprecision(3);

    for (int frame=first; frame<=last; frame++) {

        cout << endl;
        cout << "Time: " << traj->GetTime(frame) << " ps" << endl;
        cout << "Step: " << traj->GetStep(frame) << endl;
        cout << endl;

        cout << "Coordinates for group " << group << ":" << endl;
        for (int i=0;i<traj->GetNAtoms(group);i++) {
            traj->GetXYZ(frame,group,i,xyz);
            cout << xyz[X] << " " << xyz[Y] << " " << xyz[Z] << endl;
        }
        cout << endl;

        cout << "Box: " << endl;
        traj->GetBox(frame,box);
        for (int j=0; j<DIM; j++) {
            for (int k=0; k<DIM; k++) {
                cout << box[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return;

}
