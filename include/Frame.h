
/**@file
 * @brief Header for Frame class
 */
#ifndef FRAME_H
#define FRAME_H
#include "xdrfile/xdrfile.h"
#include "xdrfile/xdrfile_xtc.h"
#include "Index.h"

/**
 * @brief Class with information on one trajectory frame.
 *
 * @details A Frame contains the information on the time, the step, and the
 * coordinates and box for that time/step. rvec and matrix types come 
 * from the xdrfile library. rvec is actually a float matrix with three
 * elements. It is pointer here so that later it will be initialized
 * as an array containing the coordinates of all of the atoms of the frame.
 * The matrix type is just a 3 x 3 array. Frame objects are usually not created
 * on their own, but instead are created as a vector in a Trajectory object.
 */
class Frame {
    private:
		int natoms;
        int step;
        float time;
        rvec *x;
        matrix box; 
    public:

		/** @brief Blank constructor used in Trajectory. */
		Frame();

		/** @brief A constructor where the private data for the object is set. 
		 * @param step The step number corresponding with this simulation frame.
		 * @param time The time (in picoseconds) corresponding with this
		 * simulation frame.
		 * @param box The box dimensions for this frame.
		 * @param x The coordinates of every atom in this frame.
		 * @param natoms The number of atoms in the system.
		 * */
		Frame(int step,float time,matrix box,rvec *x,int natoms);

		/** Used in setting all of the private data for an object. Specifically
		 * this is used in the Trajectory object with a vector of Frames.  See
		 * above.
		 * */
		void Set(int step,float time,matrix box,rvec *x,int natoms);

		/** 
		 * @brief the simulation time in picoseconds of this frame. 
		 * @return Time
		 */
        float GetTime() const;

		/** 
		 * @brief the simulation step corresponding with this frame.
		 * @return Step
		 */
        int GetStep() const;

		/**
		 * @brief Gets the coordinates of a specific atom in the entire system.
		 * @details Gets the cartesian coordinates for the atom specified at this frame
		 * and returns it as a vector.
		 * @param atom The number corresponding with the atom in the entire
		 * system.
		 * @param frame Number of the frame desired.
		 * @return Vector with X, Y, and Z coordinates of the atom specified.
		 */
		vector <double> GetXYZ(int atom) const;

		/**
		 * @brief Gets all of the coordinates for the system for this frame.
		 * @details
		 * @return  A two dimensional vector with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number.
		 * The second dimension contains the X, Y, and Z positions.
		 */
		vector < vector <double> > GetXYZ() const;

		/**
		 * @brief Gets the coordinates for all atoma in a group.
		 * @details Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 * @param groupName Name of index group in which atom is located.
		 * @param index The index object containing the group specified.
		 * @return  A two dimensional vector with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number
		 * in the index group.
		 * The second dimension contains the X, Y, and Z positions.
		 */
		vector < vector <double> > GetXYZ(Index index, string group) const;

		/**
		 * @brief Gets the triclinic box dimensions for this frame.
		 * @details Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 * @return Two-dimensional array with three elements in each 
		 * dimension, corresponding to a triclinic box.
		 */
		vector < vector <double> >  GetBox() const;

		/**
		 * @brief Gets the coordinates of a specific atom in the entire system.
		 * @details Gets the cartesian coordinates for the atom specified at this frame.
		 * "rvec" is a one-dimensional array with three entries,
		 * corresponding to the X, Y, and Z coordinates. 
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param atomNumber The number corresponding with the atom in the entire
		 * system.
		 * @param xyz Array with X, Y, and Z coordinates of the atom specified.
		 */
		void GetXYZ(int atomNumber, rvec xyz) const;

		/**
		 * @brief Gets all of the coordinates for the system for this frame.
		 * @details
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param xyz[] A two dimensional array with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number.
		 * The second dimension contains the X, Y, and Z positions.
		 * @param natoms The number of atoms in the system.
		 */
		void GetXYZ(rvec xyz[], int natoms) const;

		/**
		 * @brief Gets the coordinates for a all atoms in a group.
		 * @details Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 * This is the old way.
		 * The new way is to return a vector (see above).
		 * @param groupName Name of index group in which atom is located.
		 * @param xyz Array with X, Y, and Z coordinates of the atom specified.
		 * @param index The index object containing the group specified.
		 */
		void GetXYZ(rvec xyz[], Index index, string groupName) const;

		/**
		 * @brief Gets the triclinic box dimensions for this frame.
		 * @details Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 * This is the old way. The new way returns a vector (see above).
		 * @param box Two-dimensional array with three elements in each 
		 * dimension, corresponding to a triclinic box.
		 */
		void GetBox(matrix box) const;

		/**
		 * @brief Gets the volume of the box at this frame.
		 * @return Box volume.
		 */
		double GetBoxVolume() const;
};

#endif
