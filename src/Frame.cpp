
#include "Frame.h"
#include "Trajectory.h"

Frame::Frame() {
}

Frame::Frame(int step,float time,matrix box,vector < vector <double> > x) {
	Set(step,time,box,x);
}


// Sets the info (step, time, coordinates) for this specific frame
void Frame::Set(int step,float time,matrix box,vector < vector <double> > x) {
	this->step = step;
	this->time = time;
	for (int i=0;i<DIM;i++) {
		for (int j=0;j<DIM;j++) {
			this->box[i][j] = box[i][j];
		}
	}
	this->x.resize(x.size());
	for (int i=0; i<x.size(); i++) {
		this->x.at(i).resize(DIM);
		for (int j=0; j<DIM; j++) {
			this->x.at(i).at(j) = x.at(i).at(j);
		}
	}
	return;
}

float Frame::GetTime() const {
    return time;
}

int Frame::GetStep() const {
    return step;
}

vector <double> Frame::GetXYZ(int atom) const {
	return x.at(atom);
}

vector < vector <double> > Frame::GetXYZ() const {
	return x;
}

vector < vector <double> > Frame::GetXYZ(Index index, string group) const {
	vector < vector <double> > x;
	int location;
    for (int atom=0; atom<index.GetGroupSize(group); atom++) {
	    location = index.GetLocation(group, atom);
        x.at(atom).at(X) = this->x.at(location).at(X);
        x.at(atom).at(Y) = this->x.at(location).at(Y);
        x.at(atom).at(Z) = this->x.at(location).at(Z);
    }
	return x;
}


// Below are the old functions, left for compatibility
void Frame::GetXYZ(int atom, rvec xyz) const {
    xyz[X] = x.at(atom).at(X);
    xyz[Y] = x.at(atom).at(Y);
    xyz[Z] = x.at(atom).at(Z);
	return;
}

void Frame::GetXYZ(rvec xyz[], int natoms) const {
    for (int atom=0; atom<natoms; atom++) {
        xyz[atom][X] = this->x.at(atom).at(X);
        xyz[atom][Y] = this->x.at(atom).at(Y);
        xyz[atom][Z] = this->x.at(atom).at(Z);
    }
}

void Frame::GetXYZ(rvec xyz[], Index index, string group) const {
    rvec xyzTmp;
	int location;
    for (int atom=0; atom<index.GetGroupSize(group); atom++) {
	    location = index.GetLocation(group, atom);
	    GetXYZ(atom,xyzTmp);
        xyz[atom][X] = this->x.at(location).at(X);
        xyz[atom][Y] = this->x.at(location).at(Y);
        xyz[atom][Z] = this->x.at(location).at(Z);
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
