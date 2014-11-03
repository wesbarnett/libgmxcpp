
#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <cstring>
#include <string>
#include <iostream>
#include "Frame.h"
#include "Index.h"
#include "Utils.h"
#include "xdrfile.h"
#include "xdrfile_xtc.h"
#include <stdexcept>
using namespace std;

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
		float GetTime(int frame);
		int GetStep(int frame);
        void GetXYZ(int frame, int atom, rvec xyz);
		void GetXYZ(int frame, string group, int atom, rvec xyz);
		void GetXYZ(string group, int frame, int atom, rvec xyz);
		void GetBox(int frame, matrix box);
};

#endif
