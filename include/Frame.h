
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
		/** Blank constructor used in Trajectory. */
		Frame();
		/** A constructor where the private data for the object is set. */
		Frame(int step,float time,matrix box,rvec *x);
		/** Used in setting all of the private data for an object. Specifically
		 * this is used in the Trajectory object with a vector of Frames. */
		void Set(int step,float time,matrix box,rvec *x);
		/** Returns the simulation time in picoseconds of this frame. */
        float GetTime() const;
		/** Returns the simulation step corresponding with this frame. */
        int GetStep() const;
		/** Gets the cartesian coordinates of a specific atom. *xyz* is returned. */
		void GetXYZ(int atomNumber, rvec xyz) const;
		/** Gets the coordinates of all atoms in the system. *xyz* is
		 * returned. */
		void GetXYZ(rvec xyz[], int natoms) const;
		/** Gets the coordinates of all atoms in a specific index group. *xyz*
		 * is returned. */
		void GetXYZ(rvec xyz[], Index index, string groupName) const;
		/** Gets the box dimensions for this frame. */
		void GetBox(matrix box) const;
		/** Returns the box volume for this frame. */
		double GetBoxVolume() const;
};

#endif
