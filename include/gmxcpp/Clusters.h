
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

class Clusters 
{
    public:
        Clusters(int mol_n, int atoms_per_mol);
		void do_clustering(int frame, Trajectory &traj, double rcut2);
        void do_clustering(int frame, Trajectory &traj, string group, double rcut2);
        int get_size(int clust);
        int get_index(int mol);
		vector <int> get_mol_numbers(int clust);
    private:
        vector <int> index;
        vector <int> size;
        int mol_n;
        int atoms_per_mol;
		void initialize();
		void add(int new_cluster,int old_cluster);
};

#endif
