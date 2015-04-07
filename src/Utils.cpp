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
 * @brief Some helpful utilities
 * @see Utils.h
 */

#include "gmxcpp/Utils.h"

coordinates pbc(coordinates a, triclinicbox box)
{
    coordinates b;

    vector <double> box_inv(3);
    double shift;

    b = a;

    box_inv.at(X) = ((float)1.0) / box.at(X).at(X);
    box_inv.at(Y) = ((float)1.0) / box.at(Y).at(Y);
    box_inv.at(Z) = ((float)1.0) / box.at(Z).at(Z);

    shift = round(b.at(Z) * box_inv.at(Z));
    b.at(Z) -= box.at(Z).at(Z) * shift;
    b.at(Y) -= box.at(Z).at(Y) * shift;
    b.at(X) -= box.at(Z).at(X) * shift;

    shift = round(b.at(Y) * box_inv.at(Y));
    b.at(Y) -= box.at(Y).at(Y) * shift;
    b.at(X) -= box.at(Y).at(X) * shift;

    shift = round(b.at(X) * box_inv.at(X));
    b.at(X) -= box.at(X).at(X) * shift;

    return b;
}

coordinates cross(coordinates a, coordinates b)
{
    coordinates r;

    r.at(X) = a.at(Y) * b.at(Z) - a.at(Z) * b.at(Y);
    r.at(Y) = a.at(Z) * b.at(X) - a.at(X) * b.at(Z);
    r.at(Z) = a.at(X) * b.at(Y) - a.at(Y) * b.at(X);
    return r;
}

double distance2(coordinates a, coordinates b, triclinicbox box)
{
    coordinates c = a - b;

    c = pbc(c, box);
    return dot(c, c);
}

double distance(coordinates a, coordinates b, triclinicbox box)
{
    return sqrt(distance2(a, b, box));
}

double dot(coordinates a, coordinates b)
{
    return a.at(X) * b.at(X) + a.at(Y) * b.at(Y) + a.at(Z) * b.at(Z);
}

double magnitude(coordinates x)
{
    return sqrt(dot(x, x));
}

double volume(triclinicbox box)
{
    return box.at(X).at(X) * box.at(Y).at(Y) * box.at(Z).at(Z) + \
           box.at(X).at(Y) * box.at(Y).at(Z) * box.at(Z).at(X) + \
           box.at(X).at(Z) * box.at(Y).at(X) * box.at(Z).at(Y) - \
           box.at(X).at(Z) * box.at(Y).at(Y) * box.at(Z).at(X) + \
           box.at(X).at(Y) * box.at(Y).at(X) * box.at(Z).at(Z) + \
           box.at(X).at(X) * box.at(Y).at(Z) * box.at(Z).at(Y);
}

ostream& operator<<(ostream &os, coordinates xyz)
{
    os << xyz.at(X) << " " << xyz.at(Y) << " " << xyz.at(Z) << endl;
    return os;
}

ostream& operator<<(ostream &os, triclinicbox box)
{
    for (int j = 0; j < DIM; j++) {
        for (int k = 0; k < DIM; k++)
            os << box.at(j).at(k) << " ";
        os << endl;
    }
    os << endl;
    return os;
}

bool fileExists(string filename)
{
    ifstream infile(filename.c_str());

    return infile.good();
}

/*
 *
 * Generates a point on a sphere with radius r and center c;
 * Reference:
 *
 * Marsaglia, George. Choosing a Point from the Surface of a Sphere. Ann. Math.
 * Statist. 43 (1972), no. 2, 645--646. doi:10.1214/aoms/1177692644.
 * http://projecteuclid.org/euclid.aoms/1177692644.
 *
 */
coordinates gen_sphere_point(coordinates center, double r)
{
    double xi_1;
    double xi_2;
    double zeta_1;
    double zeta_2;
    double zeta2 = 100.0;
    coordinates zeta;

    while (zeta2 > 1.0) {
        xi_1 = (double)rand() / (RAND_MAX);
        xi_2 = (double)rand() / (RAND_MAX);
        zeta_1 = 1.0 - 2.0 * xi_1;
        zeta_2 = 1.0 - 2.0 * xi_2;
        zeta2 = pow(zeta_1, 2) + pow(zeta_2, 2);
    }

    zeta.at(X) = 2.0 * zeta_1 * sqrt(1.0 - zeta2) * r + center.at(X);
    zeta.at(Y) = 2.0 * zeta_2 * sqrt(1.0 - zeta2) * r + center.at(Y);
    zeta.at(Z) = (1.0 - 2.0 * zeta2) * r + center.at(Z);

    return zeta;
}

/*
 * Generates random point on sphere of radius r but centered at origin.
 */
coordinates gen_sphere_point(double r)
{
    coordinates center;

    center.at(X) = 0.0;
    center.at(Y) = 0.0;
    center.at(Z) = 0.0;
    return gen_sphere_point(center, r);
}

/*
 * Generates random point on sphere of radius 1.0 and centered at origin.
 */
coordinates gen_sphere_point()
{
    coordinates center;

    center.at(X) = 0.0;
    center.at(Y) = 0.0;
    center.at(Z) = 0.0;
    return gen_sphere_point(center, 1.0);
}

double get_sphere_accept_ratio(vector <coordinates> sites, double r, double rand_n, triclinicbox box)
{
    coordinates rand_point;
    double dist2;
    double r2 = pow(r, 2);
    int accept_n = 0;
    int i;
    int j;
    int k;
    int sites_n = sites.size();

    for (i = 0; i < sites_n; i++) {
        for (j = 0; j < rand_n; j++) {
            rand_point = gen_sphere_point(sites.at(i), r);

            for (k = 0; k < sites_n; k++) {
                if (i != k) {
                    dist2 = distance2(sites.at(k), rand_point, box);

                    /*
                     * As soon as one site is closer to the random point than
                     * the site of interest, we can reject that random point.
                     */
                    if (dist2 < r2) goto rejectpoint;
                }
            }

            /*
             * If the distance between the random point and all of the other
             * sites in the group is greater than the distance between the
             * random point and the site of interest, that means it is closest
             * to the site of interest and is accepted.
             */
            accept_n++;

rejectpoint:
            continue;
        }
    }
    return (double)accept_n / (double)rand_n;
}

/*
 * Gets the surface area of a group of atoms using random points on a sphere.
 * The group of atoms could be a molecule or it could be just a cluster of atoms
 * close together or a combination of such.
 */
double get_surf_area(vector <coordinates> sites, double r, double rand_n, triclinicbox box)
{
    /*
     * The area for each site is simply the area of a sphere multiplied by the
     * acceptance ratio for that site. Factoring out the 4pir2 and the random
     * number generated for each site leaves the number of acceptance points for
     * each site, which we can then sum together. In other words, we can save
     * this calculation for last due to factorization and the fact that accept_n
     * is jus the sum of all accepted points.
     */
    return 4.0 * M_PI * pow(r, 2) * get_sphere_accept_ratio(sites, r, rand_n, box);
}
