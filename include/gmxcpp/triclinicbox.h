/*
 * libgmxcpp
 * Copyright (C) 2015 James W. Barnett <jbarnet4@tulane.edu>
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
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
 * @brief Header for triclinicbox class
 */

#ifndef TRICLINICBOX_H
#define TRICLINICBOX_H

#include "gmxcpp/coordinates.h"
#include "gmxcpp/xdrfile.h"
#include <vector>
using namespace std;

/** @brief Box dimensions.
 * @details This is just a two dimensional vector initialized to three
 * items in each dimension. 
 * 
 * cf. Gromacs manual 3.2
 * In the manual the box vectors are represented as:
 *
 * V1(X) V2(X) V3(X)
 *
 * V1(Y) V2(Y) V3(Y)
 *
 * V1(Z) V2(Z) V3(Z)
 *
 * In an xtc file the box vectors are actually representated as the transpose of
 * above:
 *
 * V1(X) V1(Y) V1(Z)
 *
 * V2(X) V2(Y) V2(Z)
 *
 * V3(X) V3(Y) V3(Z)
 *
 *
 * If one defines a triclinicbox named "box" here is how these match with the 2d
 * vector when reading in from a Trajectory object (X = 0, Y = 1, Z = 2; these
 * constants are set in coordinates.h):
 *
 * box.at(0).at(X) = V1(X)
 *
 * box.at(0).at(Y) = V1(Y)
 *
 * box.at(0).at(Z) = V1(Z)
 *
 * box.at(1).at(X) = V2(X)
 *
 * box.at(1).at(Y) = V2(Y)
 *
 * box.at(1).at(Z) = V2(Z)
 *
 * box.at(2).at(X) = V3(X)
 *
 * box.at(2).at(Y) = V3(Y)
 *
 * box.at(2).at(Z) = V3(Z)
 *
 * In a gro file the box vectors are represented as:
 * V1(X) V2(Y) V3(Z) V1(Y) V1(Z) V2(X) V2(Z) V3(X) V3(Y)
 *
 * Note that for Gromacs V1(Y) = V1(Z) = V2(Z) = 0
 *
 */

class triclinicbox : public vector < vector <double> > {
public:
/** Constructor, makes the 2d vector 3x3 */
triclinicbox();

/** Constructor where user provides dimensions */
triclinicbox(double x1, double x2, double x3, double y1, double y2, double y3, double z1, double z2, double z3);

/** Constructor where user provides dimensions, cubic */
triclinicbox(double x, double y, double z);
};

#endif
