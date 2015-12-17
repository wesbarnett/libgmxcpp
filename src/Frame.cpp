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

Frame::Frame() { }

Frame::Frame(int step, float time, matrix box, rvec *x, int natoms)
{
    Set(step, time, box, x, natoms);
}


// Sets the info (step, time, coordinates) for this specific frame
void Frame::Set(int step, float time, matrix box, rvec *x, int natoms)
{
    this->x.resize(natoms);
    this->step = step;
    this->time = time;
    this->natoms = natoms;

    #pragma omp parallel for
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            this->box.at(i).at(j) = box[i][j];
        }
    }

    #pragma omp parallel for
    for (int i = 0; i <natoms; i++)
    {
        this->x.at(i).at(X) = x[i][X];
        this->x.at(i).at(Y) = x[i][Y];
        this->x.at(i).at(Z) = x[i][Z];
    }

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
    return this->x.at(atom);
}

vector <coordinates> Frame::GetXYZ() const
{
    return x;
}

vector <coordinates> Frame::GetXYZ(Index index, string group) const
{
    int location;

    vector <coordinates> xyz(index.GetGroupSize(group));
    for (int atom = 0; atom < index.GetGroupSize(group); atom++) 
    {
        location = index.GetLocation(group, atom);
        xyz.at(atom) = this->x.at(location);
    }
    return xyz;
}

triclinicbox Frame::GetBox() const
{
    return this->box;
}

double Frame::GetBoxVolume() const
{
    return volume(this->box);
}
