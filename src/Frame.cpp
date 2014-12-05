
/** 
 * @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Frame class
 * @see Frame.h
 */

#include "Frame.h"

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
    xyz.at(X) = x[atom][X];
    xyz.at(Y) = x[atom][Y];
    xyz.at(Z) = x[atom][Z];
	return xyz;
}

vector <coordinates> Frame::GetXYZ() const {
	vector <coordinates> xyz;
	xyz.resize(natoms);
    for (int atom=0; atom<natoms; atom++) {
        xyz.at(atom).at(X) = this->x[atom][X];
        xyz.at(atom).at(Y) = this->x[atom][Y];
        xyz.at(atom).at(Z) = this->x[atom][Z];
    }
	return xyz;
}

vector <coordinates> Frame::GetXYZ(Index index, string group) const {
	int location;
	vector <coordinates> xyz;
	xyz.resize(index.GetGroupSize(group));
    for (int atom=0; atom<index.GetGroupSize(group); atom++) {
	    location = index.GetLocation(group, atom);
        xyz.at(atom).at(X) = this->x[location][X];
        xyz.at(atom).at(Y) = this->x[location][Y];
        xyz.at(atom).at(Z) = this->x[location][Z];
    }
	return xyz;
}

triclinicbox Frame::GetBox() const {
	triclinicbox box;
	for (int i=0; i<DIM; i++) {
		for (int j=0; j<DIM; j++) {
			box.at(i).at(j) = this->box[i][j];
		}
	}
	return box;
}

double Frame::GetBoxVolume() const {
	triclinicbox box = GetBox();
	return volume(box);
}
