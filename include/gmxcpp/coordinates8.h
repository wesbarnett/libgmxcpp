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

#ifndef COORDINATES8_H
#define COORDINATES8_H

#include "coordinates.h"
#include <immintrin.h>
using namespace std;

class coordinates8 {

public:

    union{
        __m256 mmx;
        float x[8];
    };
    union{
        __m256 mmy;
        float y[8];
    };
    union{
        __m256 mmz;
        float z[8];
    };

    coordinates8();

    coordinates8(float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 float x3, float y3, float z3,
                 float x4, float y4, float z4,
                 float x5, float y5, float z5,
                 float x6, float y6, float z6,
                 float x7, float y7, float z7,
                 float x8, float y8, float z8);

    coordinates8(coordinates a,
                 coordinates b,
                 coordinates c,
                 coordinates d,
                 coordinates e,
                 coordinates f,
                 coordinates g,
                 coordinates h);

    coordinates8 operator-(coordinates rhs);
    coordinates8 operator-(coordinates8 rhs);

    coordinates8& operator-=(coordinates rhs);
    coordinates8& operator-=(coordinates8 rhs);

};

#endif
