
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
		void Set(int step,float time,matrix box,rvec *x);
    public:
		/** Blank constructor used in Trajectory. */
		Frame();
		/** A constructor where the private data for the object is set */
		Frame(int step,float time,matrix box,rvec *x);
        float GetTime() const;
        int GetStep() const;
		void GetXYZ(int atom, rvec xyz) const;
		void GetXYZ(rvec xyz[], int natoms) const;
		void GetXYZ(rvec xyz[], Index index, string group) const;
		void GetBox(matrix box) const;
		double GetBoxVolume() const;
};

#endif
