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
 * @brief Header for triclinicbox class
 * @see triclinicbox.h
 */

#include "gmxcpp/triclinicbox.h"

triclinicbox::triclinicbox() { }

triclinicbox::triclinicbox(double x1, double x2, double x3, double y1, double y2, double y3, double z1, double z2, double z3)
{
    this->box[X][X] = x1;
    this->box[X][Y] = x2;
    this->box[X][Z] = x3;
    this->box[Y][X] = y1;
    this->box[Y][Y] = y2;
    this->box[Y][Z] = y3;
    this->box[Z][X] = z1;
    this->box[Z][Y] = z2;
    this->box[Z][Z] = z3;
}

triclinicbox::triclinicbox(double x, double y, double z)
{
    this->box[X][X] = x;
    this->box[X][Y] = 0.0;
    this->box[X][Z] = 0.0;
    this->box[Y][X] = 0.0;
    this->box[Y][Y] = y;
    this->box[Y][Z] = 0.0;
    this->box[Z][X] = 0.0;
    this->box[Z][Y] = 0.0;
    this->box[Z][Z] = z;
}

double& triclinicbox::operator()(int i)
{
    return box[i][i];
}

double& triclinicbox::operator()(int i, int j)
{
    return box[i][j];
}
