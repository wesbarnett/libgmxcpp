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
    coordinates b; // New coordinates

    vector <double> box_inv(3);
    double shift;

    b = a;

    box_inv.at(X) = ((float)1.0) / box.at(X).at(X); // 1.0 / V1(X)
    box_inv.at(Y) = ((float)1.0) / box.at(Y).at(Y); // 1.0 / V2(Y)
    box_inv.at(Z) = ((float)1.0) / box.at(Z).at(Z); // 1.0 / V3(Z)

    // Treat V3 first, since it's the shortest
    shift = round(b.at(Z) * box_inv.at(Z));
    b.at(Z) -= box.at(Z).at(Z) * shift; // V3(Z)
    b.at(Y) -= box.at(Z).at(Y) * shift; // V3(Y)
    b.at(X) -= box.at(Z).at(X) * shift; // V3(X)

    // Now treat V2 ( note that V2(Z) is always zero for Gromacs, so it is
    // omitted here)
    shift = round(b.at(Y) * box_inv.at(Y));
    b.at(Y) -= box.at(Y).at(Y) * shift; // V2(Y)
    b.at(X) -= box.at(Y).at(X) * shift; // V2(X)

    // Lastly treat V1 (V1(Y) and V1(Z) are always zero for Gromacs, so they are
    // omitted here)
    shift = round(b.at(X) * box_inv.at(X));
    b.at(X) -= box.at(X).at(X) * shift; // V1(X)

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

double distance2(coordinates a, coordinates b)
{
    coordinates c = a - b;
    return dot(c, c);
}

double distance(coordinates a, coordinates b, triclinicbox box)
{
    return sqrt(distance2(a, b, box));
}

double distance(coordinates a, coordinates b)
{
    return sqrt(distance2(a, b));
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

coordinates bond_vector(coordinates atom1, coordinates atom2, triclinicbox box)
{
	return pbc(atom1-atom2,box);

}

double bond_angle(coordinates atom1, coordinates atom2, coordinates atom3, triclinicbox box)
{
	coordinates bond1 = bond_vector(atom2,atom1,box);
	coordinates bond2 = bond_vector(atom2,atom3,box);

	double bond1_mag = magnitude(bond1);
	double bond2_mag = magnitude(bond2);
	double angle = acos(dot(bond1,bond2)/(bond1_mag*bond2_mag));

	return angle;

}

double dihedral_angle(coordinates i, coordinates j, coordinates k, coordinates l, triclinicbox box)
{
	coordinates H = bond_vector(k,l,box);
	coordinates G = bond_vector(k,j,box);
	coordinates F = bond_vector(j,i,box);
	coordinates A = cross(F,G);
	coordinates B = cross(H,G);
	coordinates cross_BA = cross(B,A);
	double A_mag = magnitude(A);
	double B_mag = magnitude(B);
	double G_mag = magnitude(G);
	double sin_phi = dot(cross_BA,G)/(A_mag * B_mag *G_mag);
	double cos_phi = dot(A,B)/(A_mag * B_mag);
	double phi = atan2(sin_phi,cos_phi);
	return phi;
}

void do_center_group(vector <coordinates> &atom, coordinates center, triclinicbox box)
{
    coordinates r;
    int atom_n = atom.size();
    int i;

    for (i = 0; i < atom_n; i++)
    {
        r = pbc(center-atom.at(i),box);
        atom.at(i) = center - r;
    }
    return;
}

coordinates center_of_mass(vector <coordinates> atom, vector <double> mass)
{
    if (mass.size() != atom.size()) 
        throw runtime_error("A mass needs to be specified for each atom in com calculation.");

    coordinates com(0.0,0.0,0.0);
    double total_mass = 0.0;
    int atom_n = atom.size();
    int i;

    for (i = 0; i < atom_n; i++)
    {
        com += atom.at(i) * mass.at(i);
        total_mass += mass.at(i);
    }
    com /= total_mass;

    return com;
}

/* assumes box is cubic: TODO: transform triclinic box into cubic */
/* Ref: Bai, L. and Breen, David. Calculating Center of Mass in an Unbounded 2D Environment
 * doi: 10.1080/2151237X.2008.10129266
 */
coordinates center_of_geometry(vector <coordinates> atom, triclinicbox box)
{

    coordinates cog(0.0,0.0,0.0); // geometric center
    int atom_n = atom.size();
    int i;
	int j;

	double theta;
	double xi;
	double sigma;

    /* Transform each coordinate to a circle, then transform the average back.
     * This removes periodic affects in order to get the center of geometry */
	for (j = 0; j < DIM; j++)
	{
		xi = 0.0;
		sigma = 0.0;
		for (i = 0; i < atom_n; i++)
		{
			theta = atom.at(i).at(j) / (box.at(j).at(j)) * 2.0 * M_PI;
			sigma += cos(theta);
			xi += sin(theta);
		}
		xi /= (double)atom_n;
		sigma /= (double)atom_n;

		theta = atan2(-xi,-sigma)+ M_PI;

		cog.at(j) = box.at(j).at(j) * theta / ( 2.0 * M_PI);
	}

    return cog;

}

coordinates center_of_mass(vector <coordinates> atom, vector <double> mass, triclinicbox box)
{
    if (mass.size() != atom.size()) 
        throw runtime_error("A mass needs to be specified for each atom in com calculation.");
    /* Get the center of geometry of the group, taking into account periodic
     * effects. Then center the group around the cog. After that calculate
     * center of mass. */

    coordinates cog;
    coordinates com;
    cog = center_of_geometry(atom, box);
    do_center_group(atom, cog, box);
    com = center_of_mass(atom, mass);

    return com;
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
