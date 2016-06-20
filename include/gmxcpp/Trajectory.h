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
#include "omp.h"
#include <string>
#include "gmxcpp/Frame.h"
#include "gmxcpp/Index.h"
#include "gmxcpp/Utils.h"
#include "gmxcpp/coordinates.h"
#include "gmxcpp/cubicbox.h"
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

/* The name of the .xtc file. */
string filename;

/* Part of the construction process */
void init(string filename, int b, int s, int e);

/* Opens the xtc file */
void open(string filename);

/* Reads a single frame. */
int readFrame();

/* Reads a frame, but does not save it to the vector of Frame objects. */
int skipFrame();

/* Closes the xtc file. */
void close();

/* Keeps track of the frames being read in (esp. when different than those
 * frames saved. */
int count;

/* Vector of Frame objects which contain all the data in the trajectory. */
vector <Frame> frameArray;

/* Index object containing all group names, sizes, and indices for the trajectory. */
Index index;

/* Special file pointer required by libxdrfile to read in XTC files. */
XDRFILE *xd;

/* Precision of coordinates. */
float prec;

/* Number of frames in the Trajectory object. */
int nframes;

/* Number of atoms in the simulation. */
int natoms;

public:

Trajectory();

virtual ~Trajectory();

/**
 *  @brief Constructor where only XTC file is read.
 *
 *  @details Constructor of Trajectory object in which entire system is read into a vector of Frame objects.
 *
 *  @param xtcfile Name of the Gromacs XTC file to be read in.
 *  @param b First frame to be read in. By default, starts at the first frame
 *  (frame 0).
 *  @param s Read in every sth frame.
 *  @param e Stop reading at this frame. -1 means read until the end of the
 *  file.
 */
Trajectory(string xtcfile, int b = 0, int s = 1, int e = -1);

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
 *  @param b First frame to be read in. By default, starts at the first frame
 *  (frame 0).
 *  @param s Read in every sth frame.
 *  @param e Stop reading at this frame. -1 means read until the end of the
 *  file.
 */
Trajectory(string xtcfile, Index index, int b = 0, int s = 1, int e = -1);

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
 *  @param b First frame to be read in. By default, starts at the first frame
 *  (frame 0).
 *  @param s Read in every sth frame.
 *  @param e Stop reading at this frame. -1 means read until the end of the
 *  file.
 */
Trajectory(string xtcfile, string ndxfile, int b = 0, int s = 1, int e = -1);

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
coordinates GetXYZ(int frame, int atom) const;

/**
 * @brief Gets the coordinates for a specific atom in a group.
 * @details Gets the cartesian coordinates for the atom specified in the specific
 * index group for this frame.
 * @param frame Number of the frame desired.
 * @param groupName Name of index group in which atom is located.
 * @param atom The number corresponding with the atom in the index
 * group. Note that this is **not** the same number corresponding with
 * the system. That is, the atom may be the 5th atom in the system, but
 * it may be the 2nd atom in the group. This is where it is located in
 * the group.
 * @return Vector with X, Y, and Z coordinates of the atom specified.
 */
coordinates GetXYZ(int frame, string groupName, int atom) const;

/**
 * @brief Gets all of the coordinates for the system for a specific
 * frame.
 * @param frame Number of the frame desired.
 * @return A two dimensional vector with all cartesian coordinates
 * for the system at this frame. The first dimension is the atom number.
 * The second dimension contains the X, Y, and Z positions.
 */
vector <coordinates> GetXYZ(int frame) const;

/**
 * @brief Gets all of the coordinates for an index group for a specific
 * frame.
 * @details
 * @param frame Number of the frame desired.
 * @param groupName Name of index group in which atom is located.
 * @return A two dimensional vector with all cartesian coordinates
 * for the system at this frame. The first dimension is the atom number
 * in the group. The second dimension contains the X, Y, and Z positions.
 */
vector <coordinates> GetXYZ(int frame, string groupName) const;

/**
 * @brief Gets the triclinic box dimensions for a frame.
 * @param frame Number of the frame desired.
 * @return  Two-dimensional array with three elements in each
 * dimension, corresponding to a triclinic box.
 */
triclinicbox GetBox(int frame) const;
cubicbox GetCubicBox(int frame) const;

/**
 * @brief Gets the volume of the box at a specific frame.
 * @return Box volume.
 * @param frame Number of the frame desired.
 */
double GetBoxVolume(int frame) const;

string GetFilename() const;

void CenterAtoms(int frame) const;
};

#endif
