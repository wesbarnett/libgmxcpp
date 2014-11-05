
#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"
#include "Trajectory.h"
#include "CommandLine.h"
using namespace std;

bool parseCommandLine(int argc,char* argv[],string *xtcfile,string *ndxfile);
void print(Trajectory *traj, int first, int last, string group, string outfile);
void printUsage(string program);

// Parses the command line, then prints data to standard out
int main(int argc, char* argv[]) {

    const string group = "C";
    const int first = 0;
    const int last = 5;
    string outfile = "out.dat";
    string xtcfile, ndxfile;

    if (!parseCommandLine(argc,argv,&xtcfile,&ndxfile)) return -1;

    Trajectory *traj = new Trajectory(xtcfile,ndxfile);

    print(traj,first,last,group,outfile);

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
        cout << "ERROR: File " << *xtcfile << " does not exist." << endl;
        return false;
    }

    if (!fileExists(*ndxfile)) {
        cout << "ERROR: File " << *ndxfile << " does not exist." << endl;
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

void print(Trajectory *traj,int first, int last, string group, string outfile) {

    matrix box;
    ofstream oFS;
    oFS.open(outfile.c_str());

    rvec xyz[traj->GetNAtoms(group)];

    cout << "Writing example data to " << outfile << "." << endl;

    if (!oFS.is_open()) {
        cout << "ERROR: Cannot open output file." << endl;
        return;
    }

    oFS << fixed << setprecision(3);

    for (int frame=first; frame<=last; frame++) {

        oFS << endl;

        oFS << "Time: " << traj->GetTime(frame) << " ps" << endl;
        oFS << "Step: " << traj->GetStep(frame) << endl;

        oFS << endl;

        oFS << "Coordinates for group " << group << ":" << endl;
        traj->GetXYZ(frame,group,xyz);
		oFS << xyz;
        for (int i=0;i<traj->GetNAtoms(group);i++) {
            oFS << xyz[i];
        }
		
        oFS << endl;

        oFS << "Box: " << endl;
        traj->GetBox(frame,box);
		oFS << box;
    }

    oFS.close();

    return;

}
