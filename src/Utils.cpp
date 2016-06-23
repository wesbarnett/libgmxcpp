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

    int shift = nearbyint(a[Z] / box(Z));
    if (shift != 0)
    {
        a[Z] -= box(Z,Z) * shift;
        a[Y] -= box(Z,Y) * shift;
        a[X] -= box(Z,X) * shift;
    }

    shift = nearbyint(a[Y] / box(Y));
    if (shift != 0)
    {
        a[Y] -= box(Y,Y) * shift;
        a[X] -= box(Y,X) * shift;
    }

    shift = nearbyint(a[X] / box(X));
    if (shift != 0)
    {
        a[X] -= box(X,X) * shift;
    }

    return a;
}

coordinates pbc(coordinates a, cubicbox box)
{

    a[Z] -= box[Z] * nearbyint(a[Z] / box[Z]);
    a[Y] -= box[Y] * nearbyint(a[Y] / box[Y]);;
    a[X] -= box[X] * nearbyint(a[X] / box[X]);;
    return a;
}

coordinates cross(coordinates a, coordinates b)
{
    return (coordinates (
        a[Y] * b[Z] - a[Z] * b[Y],
        a[Z] * b[X] - a[X] * b[Z],
        a[X] * b[Y] - a[Y] * b[X]));
}

double distance2(coordinates a, coordinates b, triclinicbox box)
{
    return dot(bond_vector(a, b, box));
}

double distance2(coordinates a, coordinates b, cubicbox box)
{
    return dot(bond_vector(a, b, box));
}

double distance2(coordinates a, coordinates b)
{
    return dot(a-b);
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
    return a[X] * b[X] + a[Y] * b[Y] + a[Z] * b[Z];
}

double dot(coordinates a)
{
    return dot(a, a);
}

double magnitude(coordinates x)
{
    return sqrt(dot(x));
}

double volume(triclinicbox box)
{
    return (box(X,X) * box(Y,Y) * box(Z,Z) +
            box(X,Y) * box(Y,Z) * box(Z,X) +
            box(X,Z) * box(Y,X) * box(Z,Y) -
            box(X,Z) * box(Y,Y) * box(Z,X) +
            box(X,Y) * box(Y,X) * box(Z,Z) +
            box(X,X) * box(Y,Z) * box(Z,Y));
}

double volume(cubicbox box)
{
    return (box[X] * box[Y] * box[Z]);
}

coordinates bond_vector(coordinates atom1, coordinates atom2, triclinicbox box)
{
	return pbc(atom1-atom2,box);
}

coordinates bond_vector(coordinates atom1, coordinates atom2, cubicbox box)
{
	return pbc(atom1-atom2,box);
}

double bond_angle(coordinates atom1, coordinates atom2, coordinates atom3, triclinicbox box)
{
	coordinates bond1 = bond_vector(atom2,atom1,box);
	coordinates bond2 = bond_vector(atom2,atom3,box);
	return acos(dot(bond1,bond2)/(magnitude(bond1)*magnitude(bond2)));
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
    // atan2(sin(phi), cos(phi));
	return atan2(dot(cross_BA,G)/(A_mag * B_mag *G_mag), dot(A,B)/(A_mag * B_mag));
}

void do_center_group(vector <coordinates> &atom, coordinates center, triclinicbox box)
{
    for (unsigned int i = 0; i < atom.size(); i++)
    {
        atom[i] = center - pbc(center-atom[i],box);
    }
    return;
}

void do_center_group(vector <coordinates> &atom, coordinates center, cubicbox box)
{
    for (unsigned int i = 0; i < atom.size(); i++)
    {
        atom[i] = center - pbc(center-atom[i],box);
    }
    return;
}

void do_center_group(vector <coordinates> &atom, cubicbox &box)
{
    coordinates center = center_of_geometry(atom, box);
    for (unsigned int i = 0; i < atom.size(); i++)
    {
        atom[i] = center - pbc(center-atom[i],box);
    }
    return;
}

coordinates center_of_mass(vector <coordinates> atom, vector <double> mass)
{
    if (mass.size() != atom.size()) 
    {
        throw runtime_error("A mass needs to be specified for each atom in com calculation.");
    }

    coordinates com(0.0,0.0,0.0);
    double total_mass = 0.0;

    for (unsigned int i = 0; i < atom.size(); i++)
    {
        com += atom[i] * mass[i];
        total_mass += mass[i];
    }
    com /= total_mass;

    return com;
}

/* assumes box is cubic: TODO: transform triclinic box into cubic */
/* Ref: Bai, L. and Breen, David. Calculating Center of Mass in an Unbounded 2D Environment
 * doi: 10.1080/2151237X.2008.10129266
 */
coordinates center_of_geometry(vector <coordinates> &atom, cubicbox &box)
{

    coordinates cog(0.0,0.0,0.0); // geometric center
    int atom_n = atom.size();

	double theta;
	double xi;
	double sigma;

    /* Transform each coordinate to a circle, then transform the average back.
     * This removes periodic affects in order to get the center of geometry */
	for (int j = 0; j < DIM; j++)
	{
		xi = 0.0;
		sigma = 0.0;
		for (int i = 0; i < atom_n; i++)
		{
			theta = atom[i][j] / (box[j]) * 2.0 * M_PI;
			sigma += cos(theta);
			xi += sin(theta);
		}
		xi /= (double)atom_n;
		sigma /= (double)atom_n;

		theta = atan2(-xi,-sigma)+ M_PI;

		cog[j] = box[j] * theta / ( 2.0 * M_PI);
	}

    return cog;

}

coordinates center_of_mass(vector <coordinates> atom, vector <double> mass, cubicbox box)
{
    if (mass.size() != atom.size()) 
        throw runtime_error("A mass needs to be specified for each atom in com calculation.");
    /* Get the center of geometry of the group, taking into account periodic
     * effects. Then center the group around the cog. After that calculate
     * center of mass. */

    coordinates cog = center_of_geometry(atom, box);
    do_center_group(atom, cog, box);
    return center_of_mass(atom, mass);
}

ostream& operator<<(ostream &os, coordinates xyz)
{
    os << xyz[X] << " " << xyz[Y] << " " << xyz[Z] << endl;
    return os;
}

ostream& operator<<(ostream &os, triclinicbox box)
{
    for (int j = 0; j < DIM; j++) 
    {
        for (int k = 0; k < DIM; k++)
        {
            os << box(j,k) << " ";
        }
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
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0,1.0);
    double xi_1;
    double xi_2;
    double zeta_1;
    double zeta_2;
    double zeta2 = 100.0;

    while (zeta2 > 1.0) 
    {
        xi_1 = dist(gen);
        xi_2 = dist(gen);
        zeta_1 = 1.0 - 2.0 * xi_1;
        zeta_2 = 1.0 - 2.0 * xi_2;
        zeta2 = pow(zeta_1, 2) + pow(zeta_2, 2);
    }

    return (coordinates (2.0 * zeta_1 * sqrt(1.0 - zeta2) * r + center[X],
                         2.0 * zeta_2 * sqrt(1.0 - zeta2) * r + center[Y],
                        (1.0 - 2.0 * zeta2) * r + center[Z]));
}

/*
 * Generates random point on sphere of radius r but centered at origin.
 */
coordinates gen_sphere_point(double r)
{
    return gen_sphere_point(coordinates(0.0, 0.0, 0.0), r);
}

/*
 * Generates random point on sphere of radius 1.0 and centered at origin.
 */
coordinates gen_sphere_point()
{
    return gen_sphere_point(coordinates(0.0, 0.0, 0.0), 1.0);
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

    for (i = 0; i < sites_n; i++) 
    {
        for (j = 0; j < rand_n; j++) 
        {
            rand_point = gen_sphere_point(sites[i], r);

            for (k = 0; k < sites_n; k++) 
            {
                if (i != k) 
                {
                    dist2 = distance2(sites[k], rand_point, box);

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
            ++accept_n;

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

void gen_rand_box_points(vector <coordinates> &xyz, triclinicbox &box, int n)
{
    xyz.clear();
    xyz.reserve(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis_x(0.0,box(X));
    uniform_real_distribution<double> dis_y(0.0,box(Y));
    uniform_real_distribution<double> dis_z(0.0,box(Z));

    for (int i = 0; i < n; i++)
    {
        xyz.push_back(coordinates(dis_x(gen), dis_y(gen), dis_z(gen)));
    }

    return;

}

void gen_rand_box_points(vector <coordinates> &xyz, cubicbox &box, int n)
{
    xyz.clear();
    xyz.reserve(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis_x(0.0,box[X]);
    uniform_real_distribution<double> dis_y(0.0,box[Y]);
    uniform_real_distribution<double> dis_z(0.0,box[Z]);

    for (int i = 0; i < n; i++)
    {
        xyz.push_back(coordinates(dis_x(gen), dis_y(gen), dis_z(gen)));
    }

    return;

}
