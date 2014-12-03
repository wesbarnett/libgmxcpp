
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

const int MAXFRAMES=100000;

/**
 * A Trajectory object contains a vector of Frame objects, plus other info
 * on the simulation (number of atoms). It also contains the special xd
 * pointer that libxdrfile needs to open the xtc file, as well as the number of
 * atoms in the system, the number of frames read in, and an Index object.
 */
class Trajectory {
	private:
		vector <Frame> frameArray;
		Index index;
        XDRFILE *xd;
        float prec;
		int nframes;
        int natoms;
        void read(int initalFrames);
		void InitXTC(string filename);
	public:
		/**
		 * Constructor, where *xtcfile* is the name of the GROMACS xtc file to
		 * be read in.
		 */
		Trajectory(string xtcfile);

		/**
		 * Constructor where then number of frames allocated is set by the
		 * programmer explicitly. By default, the constructor will only allocate
		 * 100,000 frames. This overrides that to a higher number.
		 */
		Trajectory(string xtcfile, int initialFrames);
		/**
		 * Constructor which reads in both the xtc file and a GROMACS index
		 * file.
		 */
		Trajectory(string xtcfile, string ndxfile);
		/**
		 * Constructor which reads in xtc file, index file, and the programmer
		 * sets the number of frames to allocate for manually.
		 */
		Trajectory(string filename, string ndxfile, int initialFrames);
		/**
		 * Returns the number of atoms in the sytem.
		 */
        int GetNAtoms() const;
		/** 
		 * Returns the number of atoms in a group in the system, where *group*
		 * is the name of the group in the index file.
		 */
		int GetNAtoms(string group) const;
		/** 
		 * Returns the number of frames that are in the object.
		 */
		int GetNFrames() const;
		/**
		 * Returns the time at the frame specified.
		 */
		float GetTime(int frame) const;
		/**
		 * Returns the step number at the frame specified.
		 */
		int GetStep(int frame) const;
		/**
		 * Gets the cartesian coordinates for the atom specified at the frame
		 * specified. "rvec" is a one-dimensional array with three entries,
		 * corresponding to the X, Y, and Z coordinates.
		 */
        void GetXYZ(int frame, int atom, rvec xyz) const;
		/**
		 * Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 */
		void GetXYZ(int frame, string group, int atom, rvec xyz) const;
		/**
		 * Same as above.
		 */
		void GetXYZ(string group, int frame, int atom, rvec xyz) const;
		/**
		 * Gets all of the coordinates for the system for this frame.
		 */
		void GetXYZ(int frame, rvec xyz[]) const;
		/**
		 * Gets all of the coordinates for this index group for this frame.
		 */
		void GetXYZ(int frame, string group, rvec xyz[]) const;
		/**
		 * Gets the box dimensions for this frame. *matrix* is a two dimensional
		 * array with thre elements in each dimension, corresponding to a
		 * triclinic box.
		 */
		void GetBox(int frame, matrix box) const;
		/**
		 * Returns the volume of the box for the frame specified.
		 */
		double GetBoxVolume(int frame) const;
};

#endif
