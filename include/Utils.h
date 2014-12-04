
/** @file
 * @brief Some useful functions for processing trajectories
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
#include <vector>
using namespace std;

/** X coordinate */
const int X = 0;
/** Y coordinate */
const int Y = 1;
/** Z coordinate */
const int Z = 2;

//typedef vector <double> coordinates;

/** XYZ coordinates **/
class coordinates: public vector<double> {
	public:
		coordinates() {
			this->resize(DIM);
		};
		coordinates operator-(coordinates rhs) {
			coordinates x;
			x.at(X) = this->at(X) - rhs.at(X);
			x.at(Y) = this->at(Y) - rhs.at(Y);
			x.at(Z) = this->at(Z) - rhs.at(Z);
			return x;
		}
		coordinates operator+(coordinates rhs) {
			coordinates x;
			x.at(X) = this->at(X) + rhs.at(X);
			x.at(Y) = this->at(Y) + rhs.at(Y);
			x.at(Z) = this->at(Z) + rhs.at(Z);
			return x;
		}
};

/** Box dimensions **/
class triclinicbox: public vector < vector <double> > {
	public:
		triclinicbox() {
			this->resize(DIM);
			for (int i=0; i < DIM; i++) {
				this->at(i).resize(DIM);
			}
		};
};
/** Prints out coordinates cleanly with << */
ostream& operator<<(ostream &os, coordinates xyz);

/** Prints out box coordinates cleanly with << */
ostream& operator<<(ostream &os, triclinicbox box);

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


/* OLD FUNCTIONS - kept for backwards compatilibity */
/*
 * @brief Adjusts for periodic boundary condition
 * @details User passes a vector, most likely a vector pointing from one atom
 * to another in the simulation. This function adjusts the vector such that if
 * it is longer than 1/2 the box size it accounts for the periodic boundary.
 * @param a Vector to be passed and returned.
 * @param box The box dimensions.
 */
void pbc(rvec a, matrix box);
/* @brief Calculates the cross product. OLD
 * @details Gets the cross product between vectors a and b and returns r.
 * @param a First vector to be crossed.
 * @param b Second vector to be crossed.
 * @param r The resultant vector of the cross of a and b.
 */
void cross(rvec a, rvec b, rvec r);
/* @brief Calculates the distance between atom a and atom b.
 * @return Distance
 * @param a First atom in distance calculation
 * @param b Second atom in distance calculation
 * @param box Box dimensions
 */
double distance(rvec a, rvec b, matrix box);
/* @brief Calculates the distance squared between atom a and atom b.
 * @return Distance
 * @param a First atom in distance squared calculation
 * @param b Second atom in distance squared calculation
 * @param box Box dimensions
 */
double distance2(rvec a, rvec b, matrix box);
/* @brief Calculates the magnitude of a vector
 * @return Magnitude
 * @param x Vector for which magnitude is desired
 */
double magnitude(rvec x);
/* @brief Calculates the volume of simulation box
 * @param box Box dimensions
 * @return Volume of box
 */
double volume(matrix box);
/* @brief Calculates the dot product between two vectors
 * @param a First vector in dot product
 * @param b Second vector in dot product
 * @return Dot product of a and b
 */
double dot(rvec a, rvec b);
/* @brief Adds two vectors together
 * @param a First vector to be added
 * @param b Second vector to be added
 * @param c Result of a + b
 */
void add(rvec a, rvec b, rvec c);
/* @brief Subtracts two vectors
 * @param a First vector to be subtracted
 * @param b Second vector to be subtracted
 * @param c Result of a - b
 */
void subtract(rvec a, rvec b, rvec c);
/* @brief Multiplies a vector by a constant
 * @param a Vector to be multiplied. Returned as a * x.
 * @param x Constant by which to multiply.
 */
void multiply(rvec a, double x);
/* @brief Divides a vector by a constant
 * @param a Vector to be divided. Returned as a / x.
 * @param x Constant by which to divide
 */
void divide(rvec a, double x);

/* Prints out rvec coordinates cleanly with << */
ostream& operator<<(ostream &os, rvec xyz);
/* Prints out matrix (box) coordinates cleanly with << */
ostream& operator<<(ostream &os, matrix box);


#endif
