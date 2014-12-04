
/**
 * @author James Barnett, jbarnet4@tulane.edu
 */

#include "Frame.h"
#include "Trajectory.h"

Frame::Frame() {
}

Frame::Frame(int step,float time,matrix box,rvec *x,int natoms) {
	Set(step,time,box,x,natoms);
}


// Sets the info (step, time, coordinates) for this specific frame
void Frame::Set(int step,float time,matrix box,rvec *x,int natoms) {
	this->step = step;
	this->time = time;
	for (int i=0;i<DIM;i++) {
		for (int j=0;j<DIM;j++) {
			this->box[i][j] = box[i][j];
		}
	}
	this->x = x;
	this->natoms = natoms;
	return;
}

float Frame::GetTime() const {
    return time;
}

int Frame::GetStep() const {
    return step;
}

coordinates Frame::GetXYZ(int atom) const {
	coordinates xyz;
    xyz.push_back(x[atom][X]);
    xyz.push_back(x[atom][Y]);
    xyz.push_back(x[atom][Z]);
	return xyz;
}

vector <coordinates> Frame::GetXYZ() const {
	vector <coordinates> xyz;
	xyz.resize(natoms);
    for (int atom=0; atom<natoms; atom++) {
        xyz.at(atom).push_back(this->x[atom][X]);
        xyz.at(atom).push_back(this->x[atom][Y]);
        xyz.at(atom).push_back(this->x[atom][Z]);
    }
	return xyz;
}

vector <coordinates> Frame::GetXYZ(Index index, string group) const {
	int location;
	vector <coordinates> xyz;
	xyz.resize(index.GetGroupSize(group));
    for (int atom=0; atom<index.GetGroupSize(group); atom++) {
	    location = index.GetLocation(group, atom);
        xyz.at(atom).push_back(this->x[location][X]);
        xyz.at(atom).push_back(this->x[location][Y]);
        xyz.at(atom).push_back(this->x[location][Z]);
    }
	return xyz;
}

triclinicbox Frame::GetBox() const {
	triclinicbox box;
	box.resize(3);
	for (int i=0; i<DIM; i++) {
		box.at(i).resize(3);
		for (int j=0; j<DIM; j++) {
			box.at(i).at(j) = this->box[i][j];
		}
	}
	return box;
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
