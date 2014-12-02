
#ifndef FRAME_H
#define FRAME_H
#include "xdrfile/xdrfile.h"
#include "xdrfile/xdrfile_xtc.h"
#include "Index.h"

// A frame contains the information on the time, the step, and the
// coordinates and box for that time/step. rvec and matrix types come 
// from the xdrfile library. rvec is actually a float matrix with three
// elements. It is pointer here so that later it will be initialized
// as an array containing the coordinates of all of the atoms of the frame.
// The matrix type is just a 3 x 3 array.
//
// Note that this class does not have a proper constructor or destructor. It is
// used as an array in a Trajectory object. Deleting a Frame array doesn't
// free up the memory from the x array, so that has to be done manually (and is
// done that way in the Trajectory destructor). It's advantageous to not
// automatically do this since copying coordinates between Frame objects costs
// time, so we just copy the pointer.

class Frame {
    private:
        int step;
        float time;
        rvec *x;
        matrix box; 
    public:
		void Set(int step,float time,matrix box,rvec *x);
        float GetTime();
        int GetStep();
		void GetXYZ(int atom, rvec xyz);
		void GetXYZ(rvec xyz[], int natoms);
		void GetXYZ(rvec xyz[], Index index, string group);
		void GetBox(matrix box);
		double GetBoxVolume();
};

#endif
