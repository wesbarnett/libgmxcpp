
#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <cstring>
#include <string>
#include <iostream>
#include "Frame.h"
#include "Index.h"
#include "Utils.h"
#include "xdrfile/xdrfile.h"
#include "xdrfile/xdrfile_xtc.h"
#include <stdexcept>
using namespace std;

// A trajectory object contains an array of frames, plus other info
// on the simulation (number of atoms). It also contains the special xd
// pointer that xdrfile needs to open the xtc file.
class Trajectory {
	private:
		Frame *frameArray;
		int initialFrames;
		Index index;
        XDRFILE *xd;
        float prec;
		int nframes;
        int natoms;
        void read();
		void InitXTC(string filename);
	public:
		Trajectory();
		Trajectory(string filename);
		Trajectory(string filename, int initialFrames);
		Trajectory(string filename, string ndxfile);
		Trajectory(string filename, string ndxfile, int initialFrames);
        int close();
        int GetNAtoms();
		int GetNAtoms(string group);
		int GetNFrames();
		int GetGroupSize(string group);
		float GetTime(int frame);
		int GetStep(int frame);
        void GetXYZ(int frame, int atom, rvec xyz);
		void GetXYZ(int frame, string group, int atom, rvec xyz);
		void GetXYZ(int frame, rvec xyz[]);
		void GetXYZ(int frame, string group, rvec xyz[]);
		void GetXYZ(string group, int frame, int atom, rvec xyz);
		void GetBox(int frame, matrix box);
};

#endif
