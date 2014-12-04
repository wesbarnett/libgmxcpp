
/** @file 
 * @brief Header for the Trajectory class*/

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

/** @brief Maximum number of frames to read in. */
const int MAXFRAMES=100000;

/**
 * @brief The main class in reading Gromacs files.
 *
 * @details A Trajectory object contains a vector of Frame objects, plus other info
 * on the simulation (number of atoms). It also contains the special xd
 * pointer that libxdrfile needs to open the xtc file, as well as the number of
 * atoms in the system, the number of frames read in, and an Index object.
 */
class Trajectory {
	private:

		/**
		 * @brief Vector of Frame objects which contain all the data in the
		 * trajectory.
		 */
		vector <Frame> frameArray;

		/**
		 * @brief Index object containing all group names, sizes, and indices
		 * for the trajectory.
		 */
		Index index;

		/**
		 * @brief Special file pointer required by libxdrfile to read in
		 * XTC files.
		 */
        XDRFILE *xd;

		/**
		 * @brief Precision of coordinates.
		 */
        float prec;

		/**
		 * @brief Number of frames in the trajectory.
		 */
		int nframes;

		/** @brief Number of atoms in the simulation. */
        int natoms;

		/** @brief Reads in the XTC and index files. */
        void read(int initalFrames);

		/** @brief Initializes what is necessary for reading in the XTC file */
		void InitXTC(string filename);

	public:

		/**
		 *  @brief Constructor where only XTC file is read.
		 * 
		 *  @details Constructor of Trajectory object in which entire system is read into a vector of Frame objects. 
		 *
		 *  @param xtcfile Name of the Gromacs XTC file to be read in.
		 */
		Trajectory(string xtcfile);

		/**
		 * @brief   Constructor where programmer sets maximum frames to be
		 *			read in.
		 *
		 * @details Constructor where then number of frames allocated is set by the
		 *			programmer explicitly. By default, the constructor will only allocate
		 *			100,000 frames. This overrides that to a higher number.
		 *
		 * @param xtcfile Name of the Gromacs XTC file to be read in.
		 * @param	maxFrames Maximum number of frames to read in. Default is
		 *			100,000.
		 *
		 */
		Trajectory(string xtcfile, int maxFrames);

		/**
		 *
		 * @brief Constructor which reads in both the XTC file and a GROMACS index
		 * file.
		 *
		 * @details When this constructor is used, both the Gromacs XTC file is
		 * saved in the vector of Frame objects, and the group names and index
		 * numbers for the index file are saved in an Index object.
		 *
		 * @param xtcfile Name of the Gromacs XTC file to be read in.
		 * @param ndxfile Name of the Gromacs index file to be read in.
		 */
		Trajectory(string xtcfile, string ndxfile);

		/**
		 * @brief Constructor which reads in both the XTC file and an index
		 * file and maxFrames specified.
		 *
		 * @details Constructor which reads in xtc file, index file, and the programmer
		 * sets the number of frames to allocate for manually.
		 *
		 * @param xtcfile Name of the Gromacs XTC file to be read in.
		 * @param ndxfile Name of the Gromacs index file to be read in.
		 * @param	maxFrames Maximum number of frames to read in. Default is
		 *			100,000.
		 */
		Trajectory(string xtcfile, string ndxfile, int maxFrames);

		/**
		 * @brief Gets the number of atoms in a system.
		 * @return Number of atoms.
		 */
        int GetNAtoms() const;

		/** 
		 * @brief Gets the number of atoms in an index group.
		 * @return number of atoms in the group specified.
		 * @param groupName Name of group for which number of atoms is returned.
		 */
		int GetNAtoms(string groupName) const;

		/** 
		 * @brief Gets the number of frames that were saved.
		 * @return Number of frames.
		 */
		int GetNFrames() const;

		/**
		 * @brief Gets the time at frame specified.
		 * @return Time in picoseconds.
		 * @param frame Number corresponding with the frame for which time should be returned.
		 */
		float GetTime(int frame) const;

		/**
		 * @brief Gets the step at frame specified.
		 * @return Step number.
		 * @param frame Number corresponding with the frame for which step should be returned.
		 */
		int GetStep(int frame) const;

		/**
		 * @brief Gets the coordinates of a specific atom in the entire system.
		 * @details Gets the cartesian coordinates for the atom specified at the frame
		 * specified and returns it as a vector
		 * @param atom The number corresponding with the atom in the entire
		 * system.
		 * @param frame Number of the frame desired.
		 * @return Vector with X, Y, and Z coordinates of the atom specified.
		 */
		vector <double> GetXYZ(int frame, int atom) const;

		/**
		 * @brief Gets the coordinates for a specific atom in a group.
		 * @details Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 * @param frame Number of the frame desired.
		 * @param groupName Name of index group in which atom is located.
		 * @param atom The number corresponding with the atom in the index
		 * group. Note that this is **not** the same number corresponding with
		 * the system. That is, the atom may be the 5th atom in the system, but
		 * it may be the 2nd atom in the group. This is where it is located in
		 * the group.
		 * @return Vector with X, Y, and Z coordinates of the atom specified.
		 */
		vector <double> GetXYZ(int frame, string groupName, int atom) const;

		/**
		 * @brief Gets all of the coordinates for the system for a specific
		 * frame.
		 * @param frame Number of the frame desired.
		 * @return A two dimensional vector with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number.
		 * The second dimension contains the X, Y, and Z positions.
		 */
		vector < vector <double> > GetXYZ(int frame) const;

		/**
		 * @brief Gets all of the coordinates for an index group for a specific
		 * frame.
		 * @details
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param frame Number of the frame desired.
		 * @param groupName Name of index group in which atom is located.
		 * @return A two dimensional vector with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number
		 * in the group. The second dimension contains the X, Y, and Z positions.
		 */
		vector < vector <double> > GetXYZ(int frame, string groupName) const;

		/**
		 * @brief Gets the triclinic box dimensions for a frame.
		 * @param frame Number of the frame desired.
		 * @return  Two-dimensional array with three elements in each 
		 * dimension, corresponding to a triclinic box.
		 */
		vector < vector <double> > GetBox(int frame) const;

		/**
		 * @brief Gets the coordinates of a specific atom in the entire system.
		 * @details Gets the cartesian coordinates for the atom specified at the frame
		 * specified. "rvec" is a one-dimensional array with three entries,
		 * corresponding to the X, Y, and Z coordinates. 
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param atom The number corresponding with the atom in the entire
		 * system.
		 * @param frame Number of the frame desired.
		 * @param xyz Array with X, Y, and Z coordinates of the atom specified.
		 */
        void GetXYZ(int frame, int atom, rvec xyz) const;

		/**
		 * @brief Gets the coordinates for a specific atom in a group.
		 * @details Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param frame Number of the frame desired.
		 * @param groupName Name of index group in which atom is located.
		 * @param atom The number corresponding with the atom in the index
		 * group. Note that this is **not** the same number corresponding with
		 * the system. That is, the atom may be the 5th atom in the system, but
		 * it may be the 2nd atom in the group. This is where it is located in
		 * the group.
		 * @param xyz Array with X, Y, and Z coordinates of the atom specified.
		 */
		void GetXYZ(int frame, string groupName, int atom, rvec xyz) const;

		/**
		 * Same as above.
		 */
		void GetXYZ(string group, int frame, int atom, rvec xyz) const;

		/**
		 * @brief Gets all of the coordinates for the system for a specific
		 * frame.
		 * @details
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param frame Number of the frame desired.
		 * @param xyz[] A two dimensional array with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number.
		 * The second dimension contains the X, Y, and Z positions.
		 */
		void GetXYZ(int frame, rvec xyz[]) const;

		/**
		 * @brief Gets all of the coordinates for an index group for a specific
		 * frame.
		 * @details
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param frame Number of the frame desired.
		 * @param groupName Name of index group in which atom is located.
		 * @param xyz[] A two dimensional array with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number.
		 * The second dimension contains the X, Y, and Z positions.
		 */
		void GetXYZ(int frame, string groupName, rvec xyz[]) const;

		/**
		 * @brief Gets the triclinic box dimensions for a frame.
		 * @param frame Number of the frame desired.
		 * @param box Two-dimensional array with three elements in each 
		 * dimension, corresponding to a triclinic box.
		 */
		void GetBox(int frame, matrix box) const;

		/**
		 * @brief Gets the volume of the box at a specific frame.
		 * @return Box volume.
		 * @param frame Number of the frame desired.
		 */
		double GetBoxVolume(int frame) const;
};

#endif
