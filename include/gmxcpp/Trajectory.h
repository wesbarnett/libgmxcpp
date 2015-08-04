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
 * @brief Header for the Trajectory class
 * */

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <cstring>
#include <string>
#include <iostream>
#include "gmxcpp/Frame.h"
#include "gmxcpp/Index.h"
#include "gmxcpp/Utils.h"
#include "gmxcpp/coordinates.h"
#include "gmxcpp/triclinicbox.h"
#include "gmxcpp/xdrfile.h"
#include "gmxcpp/xdrfile_xtc.h"
#include <stdexcept>
using namespace std;

/**
 * @brief The main class in reading Gromacs files.
 *
 * @details A Trajectory object contains a vector of Frame objects, plus other info
 * on the simulation (number of atoms). It also contains the special xd
 * pointer that libxdrfile needs to open the xtc file, as well as the number of
 * atoms in the system, the number of frames read in, and an Index object.
 */
class Trajectory {
private:

/**
 * @brief Vector of Frame objects which contain all the data in the
 * trajectory.
 */
vector <Frame> frameArray;

/**
 * @brief Index object containing all group names, sizes, and indices
 * for the trajectory.
 */
Index index;

/**
 * @brief Special file pointer required by libxdrfile to read in
 * XTC files.
 */
XDRFILE *xd;

/**
 * @brief Precision of coordinates.
 */
float prec;

/**
 * @brief Number of frames in the trajectory.
 */
int nframes;

/** @brief Number of atoms in the simulation. */
int natoms;

/** @brief Reads in the XTC and index files. */
void read();

/** @brief Initializes what is necessary for reading in the XTC file */
void InitXTC(string filename);

public:

/**
 *  @brief Constructor where only XTC file is read.
 *
 *  @details Constructor of Trajectory object in which entire system is read into a vector of Frame objects.
 *
 *  @param xtcfile Name of the Gromacs XTC file to be read in.
 */
Trajectory(string xtcfile);

/**
 *
 * @brief Constructor which reads in both the XTC file and incorporates a
 * previously read in Index object.
 *
 * @details When this constructor is used, both the Gromacs XTC file is
 * saved in the vector of Frame objects, and the group names and index
 * numbers from an Index object are copied into the Trajectory object.
 *
 * @param xtcfile Name of the Gromacs XTC file to be read in.
 * @param index The Index object which has already had its index file read in.
 */
Trajectory(string xtcfile, Index index);

/**
 *
 * @brief Constructor which reads in both the XTC file and a GROMACS index
 * file.
 *
 * @details When this constructor is used, both the Gromacs XTC file is
 * saved in the vector of Frame objects, and the group names and index
 * numbers for the index file are saved in an Index object.
 *
 * @param xtcfile Name of the Gromacs XTC file to be read in.
 * @param ndxfile Name of the Gromacs index file to be read in.
 */
Trajectory(string xtcfile, string ndxfile);

/**
 * @brief Gets the number of atoms in a system.
 * @return Number of atoms.
 */
int GetNAtoms() const;

/**
 * @brief Gets the number of atoms in an index group.
 * @return number of atoms in the group specified.
 * @param groupName Name of group for which number of atoms is returned.
 */
int GetNAtoms(string groupName) const;

/**
 * @brief Gets the number of frames that were saved.
 * @return Number of frames.
 */
int GetNFrames() const;

/**
 * @brief Gets the time at frame specified.
 * @return Time in picoseconds.
 * @param frame Number corresponding with the frame for which time should be returned.
 */
float GetTime(int frame) const;

/**
 * @brief Gets the step at frame specified.
 * @return Step number.
 * @param frame Number corresponding with the frame for which step should be returned.
 */
int GetStep(int frame) const;

/**
 * @brief Gets the coordinates of a specific atom in the entire system.
 * @details Gets the cartesian coordinates for the atom specified at the frame
 * specified and returns it as a vector
 * @param atom The number corresponding with the atom in the entire
 * system.
 * @param frame Number of the frame desired.
 * @return Vector with X, Y, and Z coordinates of the atom specified.
 */
coordinates *GetXYZ(int frame, int atom);

/**
 * @brief Gets the coordinates for a specific atom in a group.
 * @details Gets the cartesian coordinates for the atom specified in the specific
 * index group for this frame.
 * @see coordinates
 * @param frame Number of the frame desired.
 * @param groupName Name of index group in which atom is located.
 * @param atom The number corresponding with the atom in the index
 * group. Note that this is **not** the same number corresponding with
 * the system. That is, the atom may be the 5th atom in the system, but
 * it may be the 2nd atom in the group. This is where it is located in
 * the group.
 * @return Vector with X, Y, and Z coordinates of the atom specified.
 */
//coordinates GetXYZ(int frame, string groupName, int atom) const;
coordinates *GetXYZ(int frame, string groupName, int atom);

/**
 * @brief Gets all of the coordinates for the system for a specific
 * frame.
 * @see coordinates
 * @param frame Number of the frame desired.
 * @return A two dimensional vector with all cartesian coordinates
 * for the system at this frame. The first dimension is the atom number.
 * The second dimension contains the X, Y, and Z positions.
 */
//TODO: remove?
vector <coordinates> GetXYZ(int frame) const;


/**
 * @brief Gets the triclinic box dimensions for a frame.
 * @param frame Number of the frame desired.
 * @see triclinicbox
 * @return  Two-dimensional array with three elements in each
 * dimension, corresponding to a triclinic box.
 */
triclinicbox *GetBox(int frame);

};

#endif
