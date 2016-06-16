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
 * @brief Header for cubicbox_m256 class
 * @see cubicbox_m256.h
 */

#include "gmxcpp/cubicbox_m256.h"

cubicbox_m256::cubicbox_m256() { }

cubicbox_m256::cubicbox_m256(float x, float y, float z)
{
    mmz = _mm256_set1_ps(z);
    mmy = _mm256_set1_ps(y);
    mmx = _mm256_set1_ps(x);
}


float& cubicbox_m256::operator[](int i)
{
    switch(i)
    {
        case 0:
            return x[0];
        case 1:
            return y[0];
        case 2:
            return z[0];
    }
//TODO
}

const float& cubicbox_m256::operator[](int i) const
{
    switch(i)
    {
        case 0:
            return x[0];
        case 1:
            return y[0];
        case 2:
            return z[0];
    }
//TODO
}

