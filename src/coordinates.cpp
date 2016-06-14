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
 * @brief Header for coordinates class
 * @see coordinates.h
 */

#include "gmxcpp/coordinates.h"

coordinates::coordinates(double x, double y, double z)
{
    this->r[X] = x;
    this->r[Y] = y;
    this->r[Z] = z;
}

coordinates::coordinates(){ }

double& coordinates::operator[](int i)
{
    return r[i];
}

void coordinates::set(double x, double y, double z)
{
    this->r[X] = x;
    this->r[Y] = y;
    this->r[Z] = z;
    return;
}

coordinates coordinates::operator-(coordinates rhs)
{
    coordinates x;
    x[X] = r[X] - rhs[X];
    x[Y] = r[Y] - rhs[Y];
    x[Z] = r[Z] - rhs[Z];
    return x;
}

void coordinates::operator-=(coordinates rhs)
{
    r[X] -= rhs[X];
    r[Y] -= rhs[Y];
    r[Z] -= rhs[Z];
    return;
}

coordinates coordinates::operator+(coordinates rhs)
{
    coordinates x;

    x[X] = r[X] + rhs[X];
    x[Y] = r[Y] + rhs[Y];
    x[Z] = r[Z] + rhs[Z];
    return x;
}

void coordinates::operator+=(coordinates rhs)
{
    r[X] += rhs[X];
    r[Y] += rhs[Y];
    r[Z] += rhs[Z];
}

coordinates coordinates::operator/(double rhs)
{
    coordinates x;
    x[X] = r[X] / rhs;
    x[Y] = r[Y] / rhs;
    x[Z] = r[Z] / rhs;
    return x;
}

void coordinates::operator/=(double rhs)
{
    r[X] /= rhs;
    r[Y] /= rhs;
    r[Z] /= rhs;
}

coordinates operator*(coordinates lhs, double rhs)
{
    coordinates x;
    x[X] = lhs[X] * rhs;
    x[Y] = lhs[Y] * rhs;
    x[Z] = lhs[Z] * rhs;
    return x;
}

coordinates operator*(double lhs, coordinates rhs)
{
    coordinates x;
    x[X] = rhs[X] * lhs;
    x[Y] = rhs[Y] * lhs;
    x[Z] = rhs[Z] * lhs;
    return x;
}

void coordinates::operator*=(double rhs)
{
    r[X] *= rhs;
    r[Y] *= rhs;
    r[Z] *= rhs;
}

void coordinates::operator=(double rhs)
{
    r[X] = rhs;
    r[Y] = rhs;
    r[Z] = rhs;
    return;
}

