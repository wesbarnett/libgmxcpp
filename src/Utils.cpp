
/**
 * @author James Barnett, jbarnet4@tulane.edu
 */

#include "Utils.h"

coordinates::coordinates() {
	this->resize(DIM);
};

coordinates coordinates::operator-(coordinates rhs) {
	coordinates x;
	x.at(X) = this->at(X) - rhs.at(X);
	x.at(Y) = this->at(Y) - rhs.at(Y);
	x.at(Z) = this->at(Z) - rhs.at(Z);
	return x;
}
coordinates coordinates::operator+(coordinates rhs) {
	coordinates x;
	x.at(X) = this->at(X) + rhs.at(X);
	x.at(Y) = this->at(Y) + rhs.at(Y);
	x.at(Z) = this->at(Z) + rhs.at(Z);
	return x;
}

triclinicbox::triclinicbox() {
	this->resize(DIM);
	for (int i=0; i < DIM; i++) {
		this->at(i).resize(DIM);
	}
}

coordinates pbc(coordinates a, triclinicbox box) {

	coordinates b;
    vector <double> box_inv(3);
    double shift;

	b = a;

    box_inv.at(X) = ((float)1.0)/box.at(X).at(X);
    box_inv.at(Y) = ((float)1.0)/box.at(Y).at(Y);
    box_inv.at(Z) = ((float)1.0)/box.at(Z).at(Z);

    shift = round(b.at(Z) * box_inv.at(Z));
    b.at(Z) -= box.at(Z).at(Z) * shift;
    b.at(Y) -= box.at(Z).at(Y) * shift;
    b.at(X) -= box.at(Z).at(X) * shift;

    shift = round(b.at(Y) * box_inv.at(Y));
    b.at(Y) -= box.at(Y).at(Y) * shift;
    b.at(X) -= box.at(Y).at(X) * shift;

    shift = round(b.at(X) * box_inv.at(X));
    b.at(X) -= box.at(X).at(X) * shift;

    return b;

}

coordinates cross(coordinates a, coordinates b) {
	coordinates r;
	r.at(X) = a.at(Y)*b.at(Z)-a.at(Z)*b.at(Y);
	r.at(Y) = a.at(Z)*b.at(X)-a.at(X)*b.at(Z);
	r.at(Z) = a.at(X)*b.at(Y)-a.at(Y)*b.at(X);
}

double distance2(coordinates a, coordinates b, triclinicbox box) {

    coordinates c = a - b;
    c = pbc(c,box);
    return dot(c,c);
}

double distance(coordinates a, coordinates b, triclinicbox box) {
    return sqrt(distance2(a,b,box));
}

double dot(coordinates a, coordinates b) {
    return a.at(X)*b.at(X)+a.at(Y)*b.at(Y)+a.at(Z)*b.at(Z);
}

double magnitude(coordinates x) {
    return sqrt(dot(x,x));
}

double volume(triclinicbox box) {
    return (box.at(X).at(X)*box.at(Y).at(Y)*box.at(Z).at(Z) + \
            box.at(X).at(Y)*box.at(Y).at(Z)*box.at(Z).at(X) + \
            box.at(X).at(Z)*box.at(Y).at(X)*box.at(Z).at(Y) - \
            box.at(X).at(Z)*box.at(Y).at(Y)*box.at(Z).at(X) + \
            box.at(X).at(Y)*box.at(Y).at(X)*box.at(Z).at(Z) + \
            box.at(X).at(X)*box.at(Y).at(Z)*box.at(Z).at(Y));
}

ostream& operator<<(ostream &os, coordinates xyz) {
    os << xyz.at(X) << " " << xyz.at(Y) << " " << xyz.at(Z) << endl;
    return os;
}

ostream& operator<<(ostream &os, triclinicbox box) {
	for (int j=0; j<DIM; j++) {
		for (int k=0; k<DIM; k++) {
			os << box.at(j).at(k) << " ";
        }
        os << endl;
	}
	os << endl;
    return os;
}


/* Old functions below */
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

void divide(rvec a, double x) {
    a[X] /= x;
    a[Y] /= x;
    a[Z] /= x;
    return;
}

void multiply(rvec a, double x) {
    a[X] *= x;
    a[Y] *= x;
    a[Z] *= x;
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
