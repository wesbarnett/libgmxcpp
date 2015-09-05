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
#include "gmxcpp/Index.h"
#include "gmxcpp/Trajectory.h"
#include "gromacs/fileio/tpxio.h"
#include "gromacs/utility/smalloc.h"
#include "gromacs/topology/mtop_util.h"
#include "gromacs/topology/topology.h"
using namespace std;

/**
 * @brief The main class in reading Gromacs .tpr files.
 *
 * @details Class which stores information from a Gromacs topology (tpr) file.
 * Currently just stores the atomic charges and masses in vectors which can be
 * retrieved by getters.
 */
class Topology {
private:

	Index index;
	vector <double> q;
	vector <double> m;
	vector <string> elem;
	vector <string> atomname;
	vector <string> resname;
	void read(string tprfile);

public:

/**
 * @brief Constructor which reads in a GROMACS tpr file and associates an index
 * file with it.
 * @details Constructor which reads in the tpr file and associates an index file
 * with it. Currently only reads charges and masses of each atom into memory.
 * @param tprfile Name of the Gromacs tpr file to be read in.
 * @param ndxfile Index file to associate with this topology. Optional
 */
Topology(string tprfile, string ndxfile="none");

/**
 * @brief Gets the electric charge of the specified atom
 *
 * @param atom The atom
 * @return The charge (units specified in Gromacs manual)
 */
double GetCharge(int atom) const;

/**
 * @brief Gets the electric charge of the specified atom in an index group.
 *
 * @param atom The atom
 * @param group Index group
 * @return The charge (units specified in Gromacs manual)
 */
double GetCharge(int atom, string group) const;

/**
 * @brief Gets the electric charge of all atoms in the system
 * @return The charge of all atoms in the system (units specified in Gromacs manual)
 */
vector <double> GetCharge() const;

/**
 * @brief Gets the electric charge of the specified index group.
 * @param group Index group
 * @return The charge of all atoms in the index group (units specified in Gromacs manual)
 */
vector <double> GetCharge(string group) const;

/**
 * @brief Gets the mass of the specified atom
 *
 * @param atom The atom
 * @return The mass (units specified in Gromacs manual)
 */
double GetMass(int atom) const;

/**
 * @brief Gets the mass of the specified atom in an index group.
 * @param group Index group
 * @return The mass (units specified in Gromacs manual)
 */
double GetMass(int atom, string group) const;

/**
 * @brief Gets the mass of all atoms in the system.
 * @return The mass of all atoms in the system (units specified in Gromacs manual)
 */
vector <double> GetMass() const;

/**
 * @brief Gets the mass of the specified index group.
 * @param group Index group
 * @return The mass of all atoms in the inde group (units specified in Gromacs manual)
 */

vector <double> GetMass(string group) const;

/**
 * @brief Gets the element name of an atom.
 * @param atom The atom number
 * @return Name of the atom
 */
string GetElem(int atom);

/**
 * @brief Gets the element name of an atom in a specified group.
 * @param atom The atom number
 * @return Name of the atom
 */
string GetElem(int atom, string group);

string GetAtomName(int atom);
string GetAtomName(int atom, string group);

string GetResName(int atom);
string GetResName(int atom, string group);

};
#endif
