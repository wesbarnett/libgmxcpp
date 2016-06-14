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
 * @brief Header for Index class
 */

#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iomanip>
#include <sstream>
#include <stdexcept>
using namespace std;

/**
 * @brief Class containing index file info.
 *
 * @details Contains all information from an index file. When constructed the index
 * file is read in. The names of each group are stored in headers. The locations
 * for each group are stored in the locations vector.
 */

class Index {
private:

/* The name of the index file associated with this object. */
string filename;

/* The names of the groups in the index file. */
vector <string> headers;

/* The index locations for each group. */
vector < vector <int> > locations;

/**
 * Translates the string name of a header to its correct index integer.
 * If the header is not present in the index file, throw an exception
 * param groupName Name of the group.
 * return Integer corresponding with header (used in headers vector).
 */
int GetHeaderIndex(string groupName) const;

/**
 * brief Checks if a line read in is a header (group name).
 * param line Line read in from index file.
 * return True if is a header; false otherwise.
 */
bool isHeader(string line) const;

/**
 * @brief Checks if a file is a valid index file.
 * @return True if is valid; false otherwise.
 * @param ndxfile Name of index file.
 */
bool IsIndexFile(string ndxfile) const;

/**
 * brief Reads in the GROMACS index file specified.
 * details See above constructor. This is used in the Trajectory object
 * or when, in general, an Index object is created but no index file is
 * specified initially.
 */
bool init(string ndxfile);

/**
 * brief Prints info from index file.
 */
void PrintInfo() const;

public:

/**
 * @brief Blank constructor for Index class
 * */
Index();

/**
 * @brief Constructor which specifies index file.
 * @details When constructed the index file is read into the
 * corresponding data elements of the object and can be retrieved with
 * getter functions below.
 * @param ndxfile Name of index file to be read in.
 * */
Index(string ndxfile);

/**
 * @brief Gets the size of an index group.
 * @param groupName Name of group for which size is desired.
 * @return Size of the group.
 */
int GetGroupSize(string groupName) const;

/**
 * @brief Gets the index location of the atom in the group specified.
 * @details This returns in the index location of an atom relative to
 * the entire system. That is, if you know a specific atom's location
 * relative to an index group, i.e., it is the second atom in a group,
 * then this gives the index number for it for the entire system, i.e.,
 * the second atom in a group might be the 300th atom in the system.
 * Look at how an index file is formatted to understand more thoroughly.
 * @param groupName Name of group where at is located.
 * @param atomNumber The location of the atom in the group.
 */
int GetLocation(string groupName, int atomNumber) const;

/**
 * @brief Gets the filename associated with this object.
 */
string GetFilename() const;

};

#endif
