
/** 
 * @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Some helpful utilities
 * @see Utils.h
 */

#include "Utils.h"

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
    return r;
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

bool fileExists(string filename) {
	ifstream infile(filename.c_str());
	return infile.good();
}
