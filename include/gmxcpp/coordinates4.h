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
 * @brief Header for coordinates class
 */

#ifndef COORDINATES4_H
#define COORDINATES4_H

#include "coordinates.h"
#include <xmmintrin.h>
using namespace std;

class coordinates4 {

public:

    union{
        __m128 mmx;
        float x[4];
    };
    union{
        __m128 mmy;
        float y[4];
    };
    union{
        __m128 mmz;
        float z[4];
    };

    coordinates4();

    coordinates4(float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 float x3, float y3, float z3,
                 float x4, float y4, float z4);

    coordinates4(coordinates a,
                 coordinates b,
                 coordinates c,
                 coordinates d);

    coordinates4 operator-(coordinates rhs);
    coordinates4 operator-(coordinates4 rhs);

    coordinates4& operator-=(coordinates rhs);
    coordinates4& operator-=(coordinates4 rhs);

};

#endif
