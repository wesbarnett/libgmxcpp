
/** 
 * @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for coordinates class
 * @see coordinates.h
 */

#include "coordinates.h"

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

coordinates coordinates::operator/(double rhs) {
    coordinates x;
    x.at(X) = this->at(X) / rhs;
    x.at(Y) = this->at(Y) / rhs;
    x.at(Z) = this->at(Z) / rhs;
    return x;
}

coordinates coordinates::operator/=(double rhs) {
    coordinates x;
    x.at(X) = this->at(X) / rhs;
    x.at(Y) = this->at(Y) / rhs;
    x.at(Z) = this->at(Z) / rhs;
    return x;
}
