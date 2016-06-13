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
    this->reserve(DIM);
    this->push_back(x);
    this->push_back(y);
    this->push_back(z);
};

coordinates::coordinates()
{
    this->reserve(DIM);
};

void coordinates::set(double x, double y, double z)
{
	this->push_back(x);
	this->push_back(y);
	this->push_back(z);
    return;
}

coordinates coordinates::operator-(coordinates rhs)
{
    coordinates x;

    x.push_back(this->at(X) - rhs[X]);
    x.push_back(this->at(Y) - rhs[Y]);
    x.push_back(this->at(Z) - rhs[Z]);
    return x;
}

void coordinates::operator-=(coordinates rhs)
{
    this->at(X) -= rhs[X];
    this->at(Y) -= rhs[Y];
    this->at(Z) -= rhs[Z];
}

coordinates coordinates::operator+(coordinates rhs)
{
    coordinates x;

    x.push_back(this->at(X) + rhs[X]);
    x.push_back(this->at(Y) + rhs[Y]);
    x.push_back(this->at(Z) + rhs[Z]);
    return x;
}

void coordinates::operator+=(coordinates rhs)
{
    this->at(X) += rhs.at(X);
    this->at(Y) += rhs.at(Y);
    this->at(Z) += rhs.at(Z);
}

coordinates coordinates::operator/(double rhs)
{
    coordinates x;

    x.push_back(this->at(X) / rhs);
    x.push_back(this->at(Y) / rhs);
    x.push_back(this->at(Z) / rhs);
    return x;
}

void coordinates::operator/=(double rhs)
{
    this->at(X) /= rhs;
    this->at(Y) /= rhs;
    this->at(Z) /= rhs;
}

coordinates operator*(coordinates lhs, double rhs)
{
    coordinates x;

    x.push_back(lhs.at(X) * rhs);
    x.push_back(lhs.at(Y) * rhs);
    x.push_back(lhs.at(Z) * rhs);
    return x;
}

coordinates operator*(double lhs, coordinates rhs)
{
    coordinates x;

    x.push_back(rhs.at(X) * lhs);
    x.push_back(rhs.at(Y) * lhs);
    x.push_back(rhs.at(Z) * lhs);
    return x;
}

void coordinates::operator*=(double rhs)
{
    this->at(X) *= rhs;
    this->at(Y) *= rhs;
    this->at(Z) *= rhs;
}
