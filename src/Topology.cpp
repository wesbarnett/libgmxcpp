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

/**
 * @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date April 10, 2015
 * @brief Topology class
 * @see Topology.h
 */

#include "gmxcpp/Topology.h"
#include <iostream>
using namespace std;

// Currently just saves charges and mass to an array. TODO: save all info!
Topology::Topology(string tprfile)
{
    int i;
    int natoms;
    int status;
    gmx_mtop_t *mtop;

    snew(mtop,1);
    status = read_tpx(tprfile.c_str(),NULL,NULL,&natoms,NULL,NULL,NULL,mtop);
    t_topology top = gmx_mtop_t_to_t_topology(mtop);

    for (i = 0; i < natoms; i++)
    {
        this->q.push_back(top.atoms.atom[i].q);
        this->m.push_back(top.atoms.atom[i].m);
    }

    return;
}

// Currently is not mapped to an index file. TODO: have another call such that
// index groups can be used
double Topology::GetCharge(int atom)
{
    return this->q.at(atom);
}

double Topology::GetMass(int atom)
{
    return this->m.at(atom);
}
