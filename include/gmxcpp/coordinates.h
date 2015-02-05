
/** @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for coordinates class
 */

#ifndef COORDINATES_H
#define COORDINATES_H

#include "xdrfile/xdrfile.h"
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

		/** Adds two sets of coordinates together, element-by-element */
		coordinates operator-(coordinates rhs);

		/** Subtracts two sets of coordinates together, element-by-element */
		coordinates operator+(coordinates rhs);

		/** Divides X, Y, and Z by a scalar **/
		coordinates operator/(double rhs);

		/** Divides X, Y, and Z by a scalar **/
		coordinates operator/=(double rhs);
};

#endif
