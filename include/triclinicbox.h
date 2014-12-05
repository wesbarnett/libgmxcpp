
/** @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for triclinicbox class
 */

#ifndef TRICLINICBOX_H
#define TRICLINICBOX_H

#include "Utils.h"
#include <vector>
using namespace std;

/** @brief Box dimensions. 
 * @details This is just a two dimensional vector initialized to three
 * items in each dimension. */
class triclinicbox: public vector < vector <double> > {
	public:
		/** Constructor, makes the 2d vector 3x3 */
		triclinicbox();
};

#endif
