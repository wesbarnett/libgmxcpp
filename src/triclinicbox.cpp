
/** 
 * @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Header for triclinicbox class
 * @see triclinicbox.h
 */

#include "triclinicbox.h"

triclinicbox::triclinicbox() {
	this->resize(DIM);
	for (int i=0; i < DIM; i++) {
		this->at(i).resize(DIM);
	}
}

