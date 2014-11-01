
#include "Frame.h"

// Sets the info (step, time, coordinates) for this specific frame
void Frame::Set(int step,float time,matrix box,rvec *x) {
	this->step = step;
	this->time = time;
	for (int i=0;i<3;i++) {
		for (int j=0;j<3;j++) {
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
