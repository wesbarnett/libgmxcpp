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
 * @brief Some useful functions for processing trajectories
 * @details This file has some helper functions for calculating things like
 * distances, periodic boundary conditions, etc. This file must be included in
 * your code to use the functions and is located at 'gmxcpp/Utils.h'.
 */

#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <stdexcept>
#include <smmintrin.h>
#include <xmmintrin.h>

#include "gmxcpp/coordinates.h"
#include "gmxcpp/coordinates4.h"
#include "gmxcpp/coordinates8.h"
#include "gmxcpp/cubicbox.h"
#include "gmxcpp/cubicbox_m256.h"
#include "gmxcpp/triclinicbox.h"
#include "gmxcpp/xdrfile.h"
#include "gmxcpp/xdrfile_xtc.h"

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
coordinates pbc(coordinates a, cubicbox box);
coordinates4 pbc(coordinates4 a, triclinicbox box);
coordinates8 pbc(coordinates8 a, triclinicbox box);
coordinates8 pbc(coordinates8 a, cubicbox_m256 box);

/**
 * @brief Centers a group of atoms around another atom, removing pbc
 * @details This centers a group of atoms, using the centeral atom as the
 * reference point for removing the periodic boundary condition.
 * @param atom Group of atoms to be centered
 * @param center The central atom, may be a part of the group or not
 * @param box Simulation box
 */
void center_group(vector <coordinates> &atom, coordinates center, triclinicbox box);

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
double distance(coordinates a, coordinates b);

/** @brief Calculates the distance squared between atom a and atom b.
 * @return Distance
 * @param a First atom in distance squared calculation
 * @param b Second atom in distance squared calculation
 * @param box Box dimensions
 */
double distance2(coordinates a, coordinates b, triclinicbox box);
vector <float> distance2(coordinates4 a, coordinates b, triclinicbox box);
vector <float> distance2(coordinates8 a, coordinates b, triclinicbox box);
vector <float> distance2(coordinates8 a, coordinates b, cubicbox_m256 box);
//__m256 distance2(coordinates8 a, coordinates b, triclinicbox box);
double distance2(coordinates a, coordinates b, cubicbox box);
double distance2(coordinates a, coordinates b);

/** @brief Calculates the dot product between two vectors
 * @param a First vector in dot product
 * @param b Second vector in dot product
 * @return Dot product of a and b
 */
double dot(coordinates a, coordinates b);

/** @brief Calculates the dot product between a vector with itself
 * @param a Vector to be used in dot product
 * @return Dot product of a with itself
 */
double dot(coordinates a);

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

/** @brief Calculates the volume of simulation box
 * @param box Box dimensions
 * @return Volume of box
 */
double volume(triclinicbox box);
double volume(cubicbox_m256 box);

/** @brief Gets the bond vector between to atoms
 * @param atom1 First atom in bond
 * @param atom2 Second atom in bond
 * @param box Simulation box
 * @return bond vector
 */
coordinates bond_vector(coordinates atom1, coordinates atom2, triclinicbox box);
coordinates bond_vector(coordinates atom1, coordinates atom2, cubicbox box);

/** @brief Calculates the angle between two bonds
 * @details The central atom should be the middle input.
 * @param atom1 First atom in angle
 * @param atom2 Second atom in angle
 * @param atom3 Third atom in angle
 * @param box Simulation box
 * @return bond angle in radians
 */
double bond_angle(coordinates atom1, coordinates atom2, coordinates atom3, triclinicbox box);

/** @brief Calculates the torsion / dihedral angle from four atoms'
    positions. 
	@details Source: Blondel and Karplus, J. Comp. Chem., Vol. 17, No. 9, 1 132-1
	141 (1 996). Note that it returns in radians and that the atoms should be in order along their connections.
 * @param atom1 First atom in angle
 * @param atom2 Second atom in angle
 * @param atom3 Third atom in angle
 * @param atom4 Fourth atom in angle
 * @param box Simulation box
 * @return dihedral angle in radians
 */
double dihedral_angle(coordinates atom1, coordinates atom2, coordinates atom3, coordinates atom4, triclinicbox box);


/** Prints out coordinates cleanly with << */
ostream& operator<<(ostream &os, coordinates xyz);

/** Prints out box coordinates cleanly with << */
ostream& operator<<(ostream &os, triclinicbox box);

/** \addtogroup gen_sphere_point
 * @{
 */

/** @brief Generates a random point on a sphere.
 * @param center The center of the sphere.
 * @param r The radius of the sphere.
 * @return The coordinates of the random point.
 */
coordinates gen_sphere_point(coordinates center, double r);

/** @brief Generates a random point on a sphere at the origin.
 * @param r The radius of the sphere.
 * @return The coordinates of the random point.
 */
coordinates gen_sphere_point(double r);

/** @brief Generates a random point on a unit sphere at the origin.
 * @return The coordinates of the random point.
 */
coordinates gen_sphere_point();

/** @brief Gets the acceptance ratio of randomly generated point on a sphere.
 * @details Points are randomly generated around all sites listed in the sites
 * vector at distance r away from each site. The resulting ratio is sum of the number
 * of points accepted per points generated. In other words each site will have
 * rand_n points generated. The points that are closest to that site compared to
 * the other sites are accepted. The ratio for that site is accepted/rand_n. The
 * sum of this ratio is what is returned. This can be useful in calculating
 * surface areas or volumes of a group of atoms or molecules. See get_surf_area.
 * @param sites The coordinates of sites in the group / molecule. For example,
 * the carbons in an alkane.
 * @param r The radius to be used in determining the surface area. For example, to
 * determine the SASA use the appropriate radius.
 * @param rand_n The number of randomly generated points to be used for each
 * site.
 * @param box The box dimensions for the frame in question.
 */

/** @} */

double get_sphere_accept_ratio(vector <coordinates> sites, double r, double rand_n, triclinicbox box);

/** @brief Gets the surface area of a group of atoms.
 * @details Gets the surface area of a group of atoms (could be a molecule)
 * defined by vector of coordinates. Randomly generated points on a sphere of
 * radius r are used at each site in order to get an acceptance ratio. The
 * surface area contributed from each site is simply the surface area of a
 * sphere multiplied by the acceptance ratio for that site. The total surface
 * area is the sum of the surface areas for each site.
 * @param sites The coordinates of sites in the group / molecule. For example,
 * the carbons in an alkane.
 * @param r The radius to be used in determining the surface area. For example, to
 * determine the SASA use the appropriate radius.
 * @param rand_n The number of randomly generated points to be used for each
 * site.
 * @param box The box dimensions for the frame in question.
 */
double get_surf_area(vector <coordinates> sites, double r, double rand_n, triclinicbox box);

/** @brief Generates random points in a box.
 * @details Given a rectangular box (NOT triclinic), this generates a set of
 * random points inside the box.
 * @param xyz The vector containing the random points generated.
 * @param box The box. NOTE: Must only be rectangular/cubic.
 * @param n Number of random points to generate.
 */
void gen_rand_box_points(vector <coordinates> &xyz, triclinicbox &box, int n);

/** \addtogroup center_of_mass
 * @{
 */

/** @brief Gets the center of mass of a group of atoms.
 * @details Gets the center of mass of a group of atoms. The masses must match
 * up with the atoms specified.  Note that this version does NOT take into
 * account the periodic boundary.
 * @param atom The positions of the atoms.
 * @param mass The masses of the atoms.
 * @return The center of mass.
 */
coordinates center_of_mass(vector <coordinates> atom, vector <double> mass);

/** @brief Gets the center of mass of a group of atoms.
 * @details Gets the center of mass of a group of atoms. The masses must match
 * up with the atoms specified.  Note that this version DOES take into
 * account the periodic boundary by centering the group around the geometric
 * center first before the calculation. Note this only works for a cubic box at
 * the moment!
 * @param mass The masses of the atoms.
 * @param atom The positions of the atoms.
 * @param box The simulation box.
 * @return The center of mass.
 */
coordinates center_of_mass(vector <coordinates> atom, vector <double> mass, triclinicbox box);
/** @} */

/** @brief Gets the geometric of a group of atoms.
 * @details Gets the gemetric of a group of atoms, taking into account the
 * periodic boundary condition. * @param atom The positions of the atoms. Note
 * this only works for a cubic box at the moment.
 * @param atom The positions of the atoms.
 * @param box The simulation box.
 * @return Geometric center.
 */
coordinates center_of_geometry(vector <coordinates> atom, triclinicbox box);

/** @brief Centers a group of atoms
 * @details Centers a group of atoms around a specified point, removing the
 * periodic effects. Note that this only works for a cubic box for the moment.
 * @param atom Group of atoms to be transformed.
 * @param center The point around which to center the atoms.
 * @param box The simulation box.
 */
void do_center_group(vector <coordinates> &atom, coordinates center, triclinicbox box);

#endif
