
#include "Utils.h"

void pbc(rvec a, matrix box) {

    rvec box_inv;
    double shift;

    box_inv[X] = ((float)1.0)/box[X][X];
    box_inv[Y] = ((float)1.0)/box[Y][Y];
    box_inv[Z] = ((float)1.0)/box[Z][Z];

    shift = round(a[Z] * box_inv[Z]);
    a[Z] -= box[Z][Z] * shift;
    a[Y] -= box[Z][Y] * shift;
    a[X] -= box[Z][X] * shift;

    shift = round(a[Y] * box_inv[Y]);
    a[Y] -= box[Y][Y] * shift;
    a[X] -= box[Y][X] * shift;

    shift = round(a[X] * box_inv[X]);
    a[X] -= box[X][X] * shift;

    return;

}

void cross(rvec a, rvec b, rvec r) {
	r[X] = a[Y]*b[Z]-a[Z]*b[Y];
	r[Y] = a[Z]*b[X]-a[X]*b[Z];
	r[Z] = a[X]*b[Y]-a[Y]*b[X];
}

bool fileExists(string filename) {
	ifstream infile(filename.c_str());
	return infile.good();
}
