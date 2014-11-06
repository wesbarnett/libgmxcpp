
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

double distance2(rvec a, rvec b, matrix box) {

    rvec c;
    c[X] = a[X] - b[X];
    c[Y] = a[Y] - b[Y];
    c[Z] = a[Z] - b[Z];
    pbc(c,box);

    return dot(c,c);

}

double distance(rvec a, rvec b, matrix box) {
    return sqrt(distance2(a,b,box));
}

double volume(matrix box) {
    return (box[X][X]*box[Y][Y]*box[Z][Z] + \
            box[X][Y]*box[Y][Z]*box[Z][X] + \
            box[X][Z]*box[Y][X]*box[Z][Y] - \
            box[X][Z]*box[Y][Y]*box[Z][X] + \
            box[X][Y]*box[Y][X]*box[Z][Z] + \
            box[X][X]*box[Y][Z]*box[Z][Y]);
}

double magnitude(rvec x) {
    return sqrt(dot(x,x));
}

double dot(rvec a, rvec b) {
    return a[X]*b[X]+a[Y]*b[Y]+a[Z]*b[Z];
}

bool fileExists(string filename) {
	ifstream infile(filename.c_str());
	return infile.good();
}

void subtract(rvec a, rvec b, rvec c) {
    c[X] = a[X] - b[X];
    c[Y] = a[Y] - b[Y];
    c[Z] = a[Z] - b[Z];
    return;
}

void add(rvec a, rvec b, rvec c) {
    c[X] = a[X] + b[X];
    c[Y] = a[Y] + b[Y];
    c[Z] = a[Z] + b[Z];
    return;
}

ostream& operator<<(ostream &os, rvec xyz) {
    os << xyz[X] << " " << xyz[Y] << " " << xyz[Z] << endl;
    return os;
}

ostream& operator<<(ostream &os, matrix box) {
	for (int j=0; j<DIM; j++) {
		for (int k=0; k<DIM; k++) {
			os << box[j][k] << " ";
        }
        os << endl;
	}
	os << endl;
    return os;
}
