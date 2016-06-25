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

#include "gmxcpp/coordinates4.h"
#include <iostream>

coordinates4::coordinates4(){ }

coordinates4::coordinates4(float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 float x3, float y3, float z3,
                 float x4, float y4, float z4)
{
    mmx = _mm_set_ps(x4, x3, x2, x1);
    mmy = _mm_set_ps(y4, y3, y2, y1);
    mmz = _mm_set_ps(z4, z3, z2, z1);
}

coordinates4::coordinates4(coordinates a,
                        coordinates b,
                        coordinates c,
                        coordinates d)
{
    mmx = _mm_set_ps(d[X], c[X], b[X], a[X]);
    mmy = _mm_set_ps(d[Y], c[Y], b[Y], a[Y]);
    mmz = _mm_set_ps(d[Z], c[Z], b[Z], a[Z]);
}

coordinates4 coordinates4::operator-(coordinates4 rhs)
{
    coordinates4 x;
    x.mmx = _mm_sub_ps(mmx, rhs.mmx);
    x.mmy = _mm_sub_ps(mmy, rhs.mmy);
    x.mmz = _mm_sub_ps(mmz, rhs.mmz);
    return x;
}

coordinates4& coordinates4::operator-=(coordinates4 rhs)
{
    mmx = _mm_sub_ps(mmx, rhs.mmx);
    mmy = _mm_sub_ps(mmy, rhs.mmy);
    mmz = _mm_sub_ps(mmz, rhs.mmz);
    return *this;
}

coordinates4 coordinates4::operator-(coordinates rhs)
{
    coordinates4 x;
    x.mmx = _mm_sub_ps(mmx, _mm_set1_ps(rhs[X]));
    x.mmy = _mm_sub_ps(mmy, _mm_set1_ps(rhs[Y]));
    x.mmz = _mm_sub_ps(mmz, _mm_set1_ps(rhs[Z]));
    return x;
}

coordinates4& coordinates4::operator-=(coordinates rhs)
{
    mmx = _mm_sub_ps(mmx, _mm_set1_ps(rhs[X]));
    mmy = _mm_sub_ps(mmy, _mm_set1_ps(rhs[Y]));
    mmz = _mm_sub_ps(mmz, _mm_set1_ps(rhs[Z]));
    return *this;
}

