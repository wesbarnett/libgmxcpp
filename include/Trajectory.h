
#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <cstring>
#include <string>
#include "Frame.h"
#include "Index.h"
#include "xdrfile.h"
#include "xdrfile_xtc.h"
using namespace std;

const int X = 0;
const int Y = 1;
const int Z = 2;

// A trajectory object contains an array of frames, plus other info
// on the simulation (number of atoms). It also contains the special xd
// pointer that xdrfile needs to open the xtc file.
class Trajectory {
	private:
		int nframes;
        XDRFILE *xd;
        int natoms;
        float prec;
		int initialFrames;
		Frame *frameArray;
		Index index;
        void read();
	public:
		Trajectory();
		Trajectory(string filename);
		Trajectory(string filename, int initialFrames);
		Trajectory(string filename, string ndxfile);
        int close();
        int GetNAtoms();
		int GetNAtoms(string group);
		int GetNFrames();
		int GetGroupSize(string group);
        void GetXYZ(int frame, int atom, rvec xyz);
		void GetXYZ(int frame, string group, int atom, rvec xyz);
		void GetBox(int frame, matrix box);
};

#endif
