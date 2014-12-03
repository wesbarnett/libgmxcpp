
#ifndef FRAME_H
#define FRAME_H
#include "xdrfile/xdrfile.h"
#include "xdrfile/xdrfile_xtc.h"
#include "Index.h"

/**
 * A Frame contains the information on the time, the step, and the
 * coordinates and box for that time/step. rvec and matrix types come 
 * from the xdrfile library. rvec is actually a float matrix with three
 * elements. It is pointer here so that later it will be initialized
 * as an array containing the coordinates of all of the atoms of the frame.
 * The matrix type is just a 3 x 3 array. Frame objects are usually not created
 * on their own, but instead are created as a vector in a Trajectory object.
 */
class Frame {
    private:
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
		 * */
		Frame(int step,float time,matrix box,rvec *x);
		/** Used in setting all of the private data for an object. Specifically
		 * this is used in the Trajectory object with a vector of Frames.  See
		 * above.
		 * */
		void Set(int step,float time,matrix box,rvec *x);
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
		 * @details Gets the cartesian coordinates for the atom specified at the frame
		 * specified. "rvec" is a one-dimensional array with three entries,
		 * corresponding to the X, Y, and Z coordinates.
		 * @param atomNumber The number corresponding with the atom in the entire
		 * system.
		 * @param xyz Array with X, Y, and Z coordinates of the atom specified.
		 */
		void GetXYZ(int atomNumber, rvec xyz) const;
		/**
		 * @brief Gets all of the coordinates for the system for a specific
		 * frame.
		 * @param xyz[] A two dimensional array with all cartesian coordinates
		 * for the system at this frame. The first dimension is the atom number.
		 * The second dimension contains the X, Y, and Z positions.
		 * @param natoms The number of atoms in the system.
		 */
		void GetXYZ(rvec xyz[], int natoms) const;
		/**
		 * @brief Gets the coordinates for a specific atom in a group.
		 * @details Gets the cartesian coordinates for the atom specified in the specific
		 * index group for this frame.
		 * @param groupName Name of index group in which atom is located.
		 * @param xyz Array with X, Y, and Z coordinates of the atom specified.
		 * @param index The index object containing the group specified.
		 */
		void GetXYZ(rvec xyz[], Index index, string groupName) const;
		/**
		 * @brief Gets the triclinic box dimensions for this frame.
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
