
/** @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for coordinates class
 */

#ifndef COORDINATES_H
#define COORDINATES_H

#include "Utils.h"
#include <vector>
using namespace std;

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
};

#endif
