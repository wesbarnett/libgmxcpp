
#include "Frame.h"
#include "Trajectory.h"

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

float Frame::GetTime() {
    return time;
}

int Frame::GetStep() {
    return step;
}

void Frame::GetXYZ(int atom, rvec xyz) {
    xyz[X] = x[atom][X];
    xyz[Y] = x[atom][Y];
    xyz[Z] = x[atom][Z];
	return;
}

void Frame::GetBox(matrix box) {
	for (int i=0; i<DIM; i++) {
		for (int j=0; j<DIM; j++) {
			box[i][j] = this->box[i][j];
		}
	}
	return;
}
