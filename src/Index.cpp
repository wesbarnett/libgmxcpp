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
 * @date December 5, 2014
 * @brief Index class
 * @see Index.h
 */

#include "gmxcpp/Index.h"

Index::Index()
{
    return;
}

Index::Index(string ndxfile)
{
    Set(ndxfile);
    return;
}

bool Index::Set(string ndxfile)
{
    ifstream iFS;
    istringstream linestream;
    string line, header;
    int num;
    int groupNum = 0;

    cout << "Reading in index file " << ndxfile << "...";

    if (!IsIndexFile(ndxfile)) throw runtime_error("Not a valid index file.");


    iFS.open(ndxfile.c_str());

    if (!iFS.is_open()) throw runtime_error("Cannot open index file.");

    while (getline(iFS, line)) {
        if (isHeader(line)) {
            header = line.substr(2, line.length() - 4);
            headers.push_back(header);
            groupNum++;
        }
    }
    locations.resize(groupNum);
    iFS.close();

    groupNum = -1;
    iFS.open(ndxfile.c_str());
    while (getline(iFS, line)) {
        if (isHeader(line)) {
            groupNum++;
        } else if (line.length() != 0) {
            linestream.clear();
            linestream.str(line);
            while (linestream >> num)
                locations.at(groupNum).push_back(num);
        }
    }
    iFS.close();

    cout << "OK" << endl;

    cout << "Found the following groups: " << endl;
    PrintInfo();
    cout << "Finished reading in index file." << endl << endl;

    return true;
}

void Index::PrintInfo() const
{
    for (unsigned int i = 0; i < headers.size(); i++) {
        cout << left << "  " << setw(15) << headers.at(i);
        cout << "(" << locations.at(i).size() << " particles)" << endl;
    }
    return;
}

bool Index::IsIndexFile(string ndxfile) const
{
    ifstream iFS;
    string line;

    iFS.open(ndxfile.c_str());
    getline(iFS, line);
    iFS.close();

    if (isHeader(line)) return true;

    return false;
}

int Index::GetHeaderIndex(string header) const
{
    for (unsigned int i = 0; i < headers.size(); i++)
        if (headers.at(i) == header) return i;
    throw runtime_error("Group " + header + " is not in the index file!");
}

int Index::GetGroupSize(string header) const
{
    try {
        return locations.at(GetHeaderIndex(header)).size();
    } catch (runtime_error &excpt) {
        terminate();
    }
}

int Index::GetLocation(string header, int i) const
{
    try {
        return locations.at(GetHeaderIndex(header)).at(i) - 1;
    } catch (runtime_error &excpt) {
        terminate();
    }
}

bool Index::isHeader(string line) const
{
    return line[0] == '[' && line[line.length() - 1] == ']';
}
