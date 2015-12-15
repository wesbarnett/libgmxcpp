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
 * @date April 8, 2015
 * @brief Header for Clusters class
 */

#ifndef CLUSTERS_H
#define CLUSTERS_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "gmxcpp/Trajectory.h"

using namespace std;

/**
 * @brief Class containing clustering functions.
 *
 * @details This class is used for clustering molecules based off of a cutoff
 * distance between the various atomic sites on each molecule in question.
 * Before clustering can be performed, the object must be constructed. Then
 * "do_clustering" can be called for each frame one desires to cluster together.
 * Initially each molecule is in its own cluster of size one. After performing
 * the clustering routine one can get which molecules are part of a cluster, get
 * the cluster for which a molecule belongs, and get the size of the cluster.
 * The functions are only appropriate for clustering molecules of the same type.
 */

class Clusters
{
public:
/**
 * @brief Constructor for a Clusters object.
 * @param mol_n Total number of molecules that are going to be processed.
 * @param atoms_per_mol Number of atoms in each molecule that are going to be
 * processed.
 * */
Clusters(int mol_n, int atoms_per_mol);
/**
 * @brief Perform clustering on all molecules in xtc file.
 * @param frame The frame number to do clustering on.
 * @param traj The trajectory object with the molecules
 * @param rcut2 The cutoff length squared for determining if molecules are in
 * the same cluster. The cutoff is measured between atomic sites on each
 * molecule. If any two sites are within the cutoff the two molecules are in the
 * same cluster.
 * @details This version performs clustering on all molecules in the Trajectory
 * object. This is useful when, say, only the solutes are in the trajectory file
 * that was read in. After this function is called one can get information on the
 * clusters using the getters in this class.

 */
void do_clustering(int frame, Trajectory &traj, double rcut2);
/**
 * @brief Perform clustering on a specific index group.
 * @param frame The frame number to do clustering on.
 * @param traj The trajectory object with the molecules
 * @param group The index group to do clustering on.
 * @param group The index group to do clustering on.
 * @param rcut2 The cutoff length squared for determining if molecules are in
 * the same cluster. The cutoff is measured between atomic sites on each
 * molecule. If any two sites are within the cutoff the two molecules are in the
 * same cluster.
 * @details This version only performs the clustering routine on a specific
 * index group. After this function is called one can get information on the
 * clusters using the getters in this class.
 */
void do_clustering(int frame, Trajectory &traj, string group, double rcut2);

/**
 * @brief Get the size of the cluster.
 * @param clust The cluster number.
 * @return The cluster size, indicating the number of molecules in a cluster.
 * @details This return the number of molecules in a cluster given the cluster
 * number. This should only be performed after 'do_clustering' has been done for
 * the frame. Otherwise each cluster will be of size one. After doing
 * 'do_clustering' several clusters will be of size zero, since initially each
 * molecule is in it's own cluster.
 */
int get_size(int clust);

/**
 * @brief Get the cluster number given a molecule.
 * @param mol The number indicating the molecule of interest, corresponding to
 * the order in the trajectory object.
 * @return The cluster number to which the molecule belongs.
 * @details This should only be called after performing 'do_clustering' for a
 * frame. Initially each molecule will be in its own cluster.
 */
int get_index(int mol);

/**
 * @brief Find out which molecules belong to a cluster.
 * @param clust The cluster number.
 * @return A vector of numbers indicating which molecules are part of this
 * cluster.
 */
vector <int> get_mol_numbers(int clust);

//TODO
/**
 * @brief Get the coordinates for all atoms in a cluster
 * @param clust The cluster number
 * @return coordinates of all atoms in the cluster
 */
//vector <coordinates> get_coordinates(int clust);

private:
vector <int> index;
vector <int> size;
int mol_n;
int atoms_per_mol;
void initialize();
void add(int new_cluster, int old_cluster);
};

#endif
