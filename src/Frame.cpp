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
#include <stdio.h>
#include <string.h>

Frame::Frame() { }

Frame::~Frame()
{
    delete this->x;
}

Frame::Frame(const Frame& other)
{
    x = new rvec[other.natoms];
    memcpy(x, other.x, sizeof(float)*other.natoms*3.0);
    natoms = other.natoms;
    step = other.step;
    time = other.time;
    box[X][X] = other.box[X][X];
    box[X][Y] = other.box[X][Y];
    box[X][Z] = other.box[X][Z];
    box[Y][X] = other.box[Y][X];
    box[Y][Y] = other.box[Y][Y];
    box[Y][Z] = other.box[Y][Z];
    box[Z][X] = other.box[Z][X];
    box[Z][Y] = other.box[Z][Y];
    box[Z][Z] = other.box[Z][Z];
}

Frame& Frame::operator=(const Frame& other ) 
{
    x = new rvec[other.natoms];
    memcpy(x, other.x, sizeof(float)*other.natoms*3.0);
    natoms = other.natoms;
    step = other.step;
    time = other.time;
    box[X][X] = other.box[X][X];
    box[X][Y] = other.box[X][Y];
    box[X][Z] = other.box[X][Z];
    box[Y][X] = other.box[Y][X];
    box[Y][Y] = other.box[Y][Y];
    box[Y][Z] = other.box[Y][Z];
    box[Z][X] = other.box[Z][X];
    box[Z][Y] = other.box[Z][Y];
    box[Z][Z] = other.box[Z][Z];
    return *this;
}

Frame::Frame(int &step, float &time, matrix &box, rvec *x, int &natoms)
{
    this->step = step;
    this->time = time;
    this->box[X][X] = box[X][X];
    this->box[X][Y] = box[X][Y];
    this->box[X][Z] = box[X][Z];
    this->box[Y][X] = box[Y][X];
    this->box[Y][Y] = box[Y][Y];
    this->box[Y][Z] = box[Y][Z];
    this->box[Z][X] = box[Z][X];
    this->box[Z][Y] = box[Z][Y];
    this->box[Z][Z] = box[Z][Z];
    this->natoms = natoms;
    this->x = new rvec[natoms];
    this->x = x;
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
    return (coordinates (x[atom][X], x[atom][Y], x[atom][Z]));
}

coordinates4 Frame::GetXYZ4(int atom) const
{
    return (coordinates4 (x[atom][X], x[atom][Y], x[atom][Z],
                          x[atom+1][X], x[atom+1][Y], x[atom+1][Z],
                          x[atom+2][X], x[atom+2][Y], x[atom+2][Z],
                          x[atom+3][X], x[atom+3][Y], x[atom+3][Z]));
}

vector <coordinates> Frame::GetXYZ() const
{
    vector <coordinates> xyz(natoms);
    for (int atom = 0; atom < natoms; ++atom) 
    {
        xyz[atom][X] = this->x[atom][X];
        xyz[atom][Y] = this->x[atom][Y];
        xyz[atom][Z] = this->x[atom][Z];
    }
    return xyz;
}

vector <coordinates> Frame::GetXYZ(Index index, string group) const
{
    int location;
    const int grp_size = index.GetGroupSize(group);
    vector <coordinates> xyz(grp_size);
    for (int atom = 0; atom < grp_size; ++atom) 
    {
        location = index.GetLocation(group, atom);
        xyz[atom][X] = this->x[location][X];
        xyz[atom][Y] = this->x[location][Y];
        xyz[atom][Z] = this->x[location][Z];
    }
    return xyz;
}

triclinicbox Frame::GetBox() const
{
    return (triclinicbox(this->box[X][X],
                         this->box[X][Y],
                         this->box[X][Z],
                         this->box[Y][X],
                         this->box[Y][Y],
                         this->box[Y][Z],
                         this->box[Z][X],
                         this->box[Z][Y],
                         this->box[Z][Z]));
}

double Frame::GetBoxVolume() const
{
    return volume(this->GetBox());
}

