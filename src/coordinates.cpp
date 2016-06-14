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

coordinates::coordinates(){ }

coordinates::coordinates(double x, double y, double z)
{
    this->r[X] = x;
    this->r[Y] = y;
    this->r[Z] = z;
}

double& coordinates::operator[](int i)
{
    return r[i];
}

const double& coordinates::operator[](int i) const
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
    for (int i = 0; i < DIM; i++)
        x[i] = r[i] - rhs[i];
    return x;
}

void coordinates::operator-=(coordinates rhs)
{
    for (int i = 0; i < DIM; i++)
        r[i] -= rhs[i];
    return;
}

coordinates coordinates::operator+(coordinates rhs)
{
    coordinates x;

    for (int i = 0; i < DIM; i++)
        x[i] = r[i] + rhs[i];
    return x;
}

void coordinates::operator+=(coordinates rhs)
{
    for (int i = 0; i < DIM; i++)
        r[i] += rhs[i];
}

coordinates coordinates::operator/(double rhs)
{
    coordinates x;
    for (int i = 0; i < DIM; i++)
        x[i] = r[i] / rhs;
    return x;
}

void coordinates::operator/=(double rhs)
{
    for (int i = 0; i < DIM; i++)
        r[i] /= rhs;
}

coordinates operator*(coordinates lhs, double rhs)
{
    coordinates x;
    for (int i = 0; i < DIM; i++)
        x[i] = lhs[i] * rhs;
    return x;
}

coordinates operator*(double lhs, coordinates rhs)
{
    coordinates x;
    for (int i = 0; i < DIM; i++)
        x[i] = rhs[i] * lhs;
    return x;
}

void coordinates::operator*=(double rhs)
{
    for (int i = 0; i < DIM; i++)
        r[i] *= rhs;
    return;
}

void coordinates::operator=(double rhs)
{
    for (int i = 0; i < DIM; i++)
        r[i] = rhs;
    return;
}

