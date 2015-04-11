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
 * @date April 10, 2015
 * @brief Header for the Trajectory class
 * */

#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <string>
#include <vector>
#include "gromacs/fileio/tpxio.h"
#include "gromacs/utility/smalloc.h"
#include "gromacs/legacyheaders/mtop_util.h"
using namespace std;

/**
 * @brief The main class in reading Gromacs .tpr files.
 *
 * @details TODO
 */
class Topology {
private:

	vector <double> q;
	vector <double> m;

public:

/**
 * @brief Constructor which reads in a GROMACS tpr file.
 *
 * @details Constructor which reads in the tpr file. Currently only reads
 * charges and masses of each atom into memory.
 *
 * @param tprfile Name of the Gromacs tpr file to be read in.
 */
Topology(string tprfile);

/**
 * @brief Gets the electric charge of the specified atom
 *
 * @param atom The atom
 * @return The charge
 */
double GetCharge(int atom);

/**
 * @brief Gets the mass of the specified atom
 *
 * @param atom The atom
 * @return The mass
 */
double GetMass(int atom);

};
#endif
