
/**
 * @author James Barnett, jbarnet4@tulane.edu
 */

#include "Frame.h"
#include "Trajectory.h"

Frame::Frame() {
}

Frame::Frame(int step,float time,matrix box,rvec *x) {
	Set(step,time,box,x);
}


// Sets the info (step, time, coordinates) for this specific frame
void Frame::Set(int step,float time,matrix box,rvec *x) {
	this->step = step;
	this->time = time;
	for (int i=0;i<DIM;i++) {
		for (int j=0;j<DIM;j++) {
			this->box[i][j] = box[i][j];
		}
	}
	this->x = x;
	return;
}

float Frame::GetTime() const {
    return time;
}

int Frame::GetStep() const {
    return step;
}

void Frame::GetXYZ(int atom, rvec xyz) const {
    xyz[X] = x[atom][X];
    xyz[Y] = x[atom][Y];
    xyz[Z] = x[atom][Z];
	return;
}

void Frame::GetXYZ(rvec xyz[], int natoms) const {
    for (int atom=0; atom<natoms; atom++) {
        xyz[atom][X] = this->x[atom][X];
        xyz[atom][Y] = this->x[atom][Y];
        xyz[atom][Z] = this->x[atom][Z];
    }
}

void Frame::GetXYZ(rvec xyz[], Index index, string group) const {
    rvec xyzTmp;
	int location;
    for (int atom=0; atom<index.GetGroupSize(group); atom++) {
	    location = index.GetLocation(group, atom);
	    GetXYZ(atom,xyzTmp);
        xyz[atom][X] = this->x[location][X];
        xyz[atom][Y] = this->x[location][Y];
        xyz[atom][Z] = this->x[location][Z];
    }
}

void Frame::GetBox(matrix box) const {
	for (int i=0; i<DIM; i++) {
		for (int j=0; j<DIM; j++) {
			box[i][j] = this->box[i][j];
		}
	}
	return;
}

double Frame::GetBoxVolume() const {
	matrix box;
	GetBox(box);
	return volume(box);
}
