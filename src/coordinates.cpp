
/* 
 * libgmxcpp
 * Copyright (C) 2015 James W. Barnett <jbarnet4@tulane.edu>

 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * The full license is located in a text file titled "LICENSE" in the root
 * directory of the source.
 *
 */

/** 
 * @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for coordinates class
 * @see coordinates.h
 */

#include "gmxcpp/coordinates.h"

coordinates::coordinates(double x, double y, double z) {
	this->resize(DIM);
    this->at(X) = x;
    this->at(Y) = y;
    this->at(Z) = z;
};

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

void coordinates::operator-=(coordinates rhs) {
	this->at(X) -= rhs.at(X);
	this->at(Y) -= rhs.at(Y);
	this->at(Z) -= rhs.at(Z);
}

coordinates coordinates::operator+(coordinates rhs) {
	coordinates x;
	x.at(X) = this->at(X) + rhs.at(X);
	x.at(Y) = this->at(Y) + rhs.at(Y);
	x.at(Z) = this->at(Z) + rhs.at(Z);
	return x;
}

void coordinates::operator+=(coordinates rhs) {
	this->at(X) += rhs.at(X);
	this->at(Y) += rhs.at(Y);
    this->at(Z) += rhs.at(Z);
}

coordinates coordinates::operator/(double rhs) {
    coordinates x;
    x.at(X) = this->at(X) / rhs;
    x.at(Y) = this->at(Y) / rhs;
    x.at(Z) = this->at(Z) / rhs;
    return x;
}

void coordinates::operator/=(double rhs) {
    this->at(X) /= rhs;
    this->at(Y) /= rhs;
    this->at(Z) /= rhs;
}

coordinates coordinates::operator*(double rhs) {
    coordinates x;
    x.at(X) = this->at(X) * rhs;
    x.at(Y) = this->at(Y) * rhs;
    x.at(Z) = this->at(Z) * rhs;
    return x;
}

void coordinates::operator*=(double rhs) {
    this->at(X) *= rhs;
    this->at(Y) *= rhs;
    this->at(Z) *= rhs;
}
