
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

class Frame {
    private:
        int step;
        float time;
		vector < vector <double> > x;
		vector < vector <double> > box;
        //matrix box; 
    public:
		Frame();
		Frame(int step,float time,< vector < vector <double> >  box,vector < vector <double> > x);
		void Set(int step,float time,< vector < vector <double> > box,vector < vector <double> > x);
        float GetTime() const;
        int GetStep() const;
		void GetXYZ(int atom, rvec xyz) const;
		void GetXYZ(rvec xyz[], int natoms) const;
		void GetXYZ(rvec xyz[], Index index, string group) const;
		vector <double> GetXYZ(int atom) const;
		vector < vector <double> > GetXYZ() const;
		vector < vector <double> > GetXYZ(Index index, string group) const;
		void GetBox(matrix box) const;
		vector < vector <double> >  GetBox() const;
		double GetBoxVolume() const;
};

#endif
