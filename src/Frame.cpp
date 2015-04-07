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
 * @brief Frame class
 * @see Frame.h
 */

#include "gmxcpp/Frame.h"

Frame::Frame()
{
}

Frame::Frame(int step, float time, matrix box, rvec *x, int natoms)
{
    Set(step, time, box, x, natoms);
}


// Sets the info (step, time, coordinates) for this specific frame
void Frame::Set(int step, float time, matrix box, rvec *x, int natoms)
{
    this->step = step;
    this->time = time;
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            this->box[i][j] = box[i][j];
    this->x = x;
    this->natoms = natoms;
    return;
}

float Frame::GetTime() const
{
    return time;
}

int Frame::GetStep() const
{
    return step;
}

coordinates Frame::GetXYZ(int atom) const
{
    coordinates xyz;

    xyz.at(X) = x[atom][X];
    xyz.at(Y) = x[atom][Y];
    xyz.at(Z) = x[atom][Z];
    return xyz;
}

vector <coordinates> Frame::GetXYZ() const
{
    vector <coordinates> xyz;
    xyz.resize(natoms);
    for (int atom = 0; atom < natoms; atom++) {
        xyz.at(atom).at(X) = this->x[atom][X];
        xyz.at(atom).at(Y) = this->x[atom][Y];
        xyz.at(atom).at(Z) = this->x[atom][Z];
    }
    return xyz;
}

vector <coordinates> Frame::GetXYZ(Index index, string group) const
{
    int location;

    vector <coordinates> xyz;
    xyz.resize(index.GetGroupSize(group));
    for (int atom = 0; atom < index.GetGroupSize(group); atom++) {
        location = index.GetLocation(group, atom);
        xyz.at(atom).at(X) = this->x[location][X];
        xyz.at(atom).at(Y) = this->x[location][Y];
        xyz.at(atom).at(Z) = this->x[location][Z];
    }
    return xyz;
}

triclinicbox Frame::GetBox() const
{
    triclinicbox box;

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            box.at(i).at(j) = this->box[i][j];
    return box;
}

double Frame::GetBoxVolume() const
{
    triclinicbox box = GetBox();

    return volume(box);
}
