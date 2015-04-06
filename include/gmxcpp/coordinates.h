
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

/** @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for coordinates class
 */

#ifndef COORDINATES_H
#define COORDINATES_H

#include "gmxcpp/xdrfile.h"
#include <vector>
using namespace std;

/** X coordinate */
const int X = 0;
/** Y coordinate */
const int Y = 1;
/** Z coordinate */
const int Z = 2;

/** @brief Cartesian coordinates. 
 * @details This is just a double precision vector but 
 * it has three items automatically when contructed. Additionally
 * one can add or subtract two sets of coordinates without having
 * to operate on each X, Y, and Z part individually.*/
class coordinates: public vector<double> {
	public:

		/** Constructor, sets size of vector to 3 */
		coordinates();

		/** Constructor, sets size of vector to 3 and set actual coordinates */
		coordinates(double x, double y, double z);

		/** Subtracts two sets of coordinates together, element-by-element */
		coordinates operator-(coordinates rhs);

		/** Subtracts two sets of coordinates together, element-by-element */
		void operator-=(coordinates rhs);

		/** Adds two sets of coordinates together, element-by-element */
		coordinates operator+(coordinates rhs);

		/** Adds two sets of coordinates together, element-by-element */
		void operator+=(coordinates rhs);

		/** Divides X, Y, and Z by a scalar **/
		coordinates operator/(double rhs);

		/** Divides X, Y, and Z by a scalar **/
		void operator/=(double rhs);

		/** Multiplies X, Y, and Z by a scalar **/
		void operator*=(double rhs);

	/** Multiplies X, Y, and Z by a scalar **/
	friend coordinates operator*(coordinates lhs, double rhs);
	friend coordinates operator*(double lhs, coordinates rhs);

};

#endif
