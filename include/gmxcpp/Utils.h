
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
 * @brief Some useful functions for processing trajectories
 * @details This file has some helper functions for calculating things like
 * distances, periodic boundary conditions, etc.
 */

#ifndef UTILS_H
#define UTILS_H

#include "xdrfile/xdrfile.h"
#include "xdrfile/xdrfile_xtc.h"
#include <math.h>
#include <cmath>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"
using namespace std;

/**
 * @brief Adjusts for periodic boundary condition
 * @details User passes a vector, most likely a vector pointing from one atom
 * to another in the simulation. This function adjusts the vector such that if
 * it is longer than 1/2 the box size it accounts for the periodic boundary.
 * @param a Vector to be passed.
 * @param box The box dimensions.
 * @return Vector after pbc accounted for.
 */
coordinates pbc(coordinates a, triclinicbox box);

/** @brief Calculates the cross product.
 * @details Gets the cross product between vectors a and b and returns it.
 * @param a First vector to be crossed.
 * @param b Second vector to be crossed.
 * @return The resultant vector of the cross of a and b.
 */
coordinates cross(coordinates a, coordinates b);

/** @brief Calculates the distance between atom a and atom b.
 * @return Distance
 * @param a First atom in distance calculation
 * @param b Second atom in distance calculation
 * @param box Box dimensions
 */
double distance(coordinates a, coordinates b, triclinicbox box);

/** @brief Calculates the distance squared between atom a and atom b.
 * @return Distance
 * @param a First atom in distance squared calculation
 * @param b Second atom in distance squared calculation
 * @param box Box dimensions
 */
double distance2(coordinates a, coordinates b, triclinicbox box);

/** @brief Calculates the dot product between two vectors
 * @param a First vector in dot product
 * @param b Second vector in dot product
 * @return Dot product of a and b
 */
double dot(coordinates a, coordinates b);

/** @brief Calculates the magnitude of a vector
 * @return Magnitude
 * @param x Vector for which magnitude is desired
 */
double magnitude(coordinates x);

/** @brief Checks if a file exists
 * @param filename Name of the file to check
 * @return Whether or not the file exists
 */
bool fileExists(string filename);

/* @brief Calculates the volume of simulation box
 * @param box Box dimensions
 * @return Volume of box
 */
double volume(triclinicbox box);

/** Prints out coordinates cleanly with << */
ostream& operator<<(ostream &os, coordinates xyz);

/** Prints out box coordinates cleanly with << */
ostream& operator<<(ostream &os, triclinicbox box);


#endif
