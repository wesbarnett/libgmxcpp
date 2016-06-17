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
 * @brief Header for cubicbox8 class
 * @see cubicbox8.h
 */

#include "gmxcpp/cubicbox8.h"

cubicbox8::cubicbox8() { }

cubicbox8::cubicbox8(float x1, float y1, float z1,
                     float x2, float y2, float z2,
                     float x3, float y3, float z3,
                     float x4, float y4, float z4,
                     float x5, float y5, float z5,
                     float x6, float y6, float z6,
                     float x7, float y7, float z7,
                     float x8, float y8, float z8)
{
    mmz = _mm256_set_ps(z8, z7, z6, z5, z4, z3, z2, z1);
    mmy = _mm256_set_ps(y8, y7, y6, y5, y4, y3, y2, y1);
    mmx = _mm256_set_ps(x8, x7, x6, x5, x4, x3, x2, x1);
}
cubicbox8::cubicbox8(cubicbox a, cubicbox b, cubicbox c, cubicbox d,
                     cubicbox e, cubicbox f, cubicbox g, cubicbox h)
{
    mmx = _mm256_set_ps(h[X], g[X], f[X], e[X], d[X], c[X], b[X], a[X]);
    mmy = _mm256_set_ps(h[Y], g[Y], f[Y], e[Y], d[Y], c[Y], b[Y], a[Y]);
    mmz = _mm256_set_ps(h[Z], g[Z], f[Z], e[Z], d[Z], c[Z], b[Z], a[Z]);
}
