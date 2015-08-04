#include "gmxcpp/Clusters.h"

Clusters::Clusters(int mol_n, int atoms_per_mol)
{
    this->index.resize(mol_n);
    this->size.resize(mol_n, 0.0);
    this->mol_n = mol_n;
    this->atoms_per_mol = atoms_per_mol;
};


/* Initialize the clusters. Each molecule is initially in its own cluster. */
void Clusters::initialize()
{
    int mol_i;

    for (mol_i = 0; mol_i < this->mol_n; mol_i++) {
        this->index.at(mol_i) = mol_i;
        this->size.at(mol_i) = 1;
    }
}

void Clusters::add(int new_cluster, int old_cluster)
{
    int i;

    for (i = 0; i < this->mol_n; i++) {
        if (this->index.at(i) == old_cluster) {
            if (this->size.at(old_cluster) <= 0) cerr << "ERROR: We removed more atoms than present in a cluster!" << endl;
            this->index.at(i) = new_cluster;
            this->size.at(old_cluster) -= 1;
            this->size.at(new_cluster) += 1;
        }
    }
    return;
}

int Clusters::get_size(int clust)
{
    return this->size.at(clust);
}

int Clusters::get_index(int mol)
{
    return this->index.at(mol);
}

vector <int> Clusters::get_mol_numbers(int clust)
{
    int mol_i;

    vector <int> mol_nums;

    for (mol_i = 0; mol_i < this->mol_n; mol_i++) {
        if (this->index.at(mol_i) == clust)
            mol_nums.push_back(mol_i);

    }
    return mol_nums;
}

/*
 * TODO
vector <coordinates> Clusters::get_coordinates(int frame, Trajectory &traj, int clust)
{

	int atom_start;
	int atom_end;
	int mol_i;
	vector <coordinates> atom;
	vector <int> mol_nums;
	mol_nums = this->get_mol_numbers(clust);

	for (mol_i = 0; mol_i < this->size; mol_i++)
	{
		atom_start = mol_nums.at(mol_i) * this->atoms_per_mol;
		atom_end = (mol_nums.at(mol_i)+1) * this->atoms_per_mol;

		for (atom_i = atom_start; atom_i < atom_end; atom_i++)
		{
			atom.push_back(traj.GetXYZ(frame_i,atom_i);
		}

	}

	return atom;

}
*/

void Clusters::do_clustering(int frame, Trajectory &traj, string group, double rcut2)
{
    coordinates* atom_j_vec;
    double r2;
    int atom_counter_i;
    int atom_counter_j;
    int atom_i;
    int atom_j;
    int mol_i;
    int mol_j;
    int c_i;
    int c_j;
    triclinicbox* box;

    vector <coordinates*> atom_i_vec(atoms_per_mol);

    box = traj.GetBox(frame);
    initialize();

    for (mol_i = 0; mol_i < this->mol_n; mol_i++) {
        c_i = this->index.at(mol_i);

        /* Go ahead and save the atoms from this molecule to a vector so that we
         * don't have to keep accessing it later below. */
        atom_counter_i = mol_i * atoms_per_mol;
        for (atom_i = 0; atom_i < this->atoms_per_mol; atom_i++) {
            atom_i_vec.at(atom_i) = traj.GetXYZ(frame, group, atom_counter_i);
            atom_counter_i++;
        }

        for (mol_j = 0; mol_j < this->mol_n; mol_j++) {
            c_j = this->index.at(mol_j);

            if (c_i != c_j) {
                /* This compares every atom on the two molecules. If one pair is
                 * within the cutoff range then the two molecules should be
                 * added to the same cluster and no more checking is necessary
                 * for these two molecules. */
                for (atom_i = 0; atom_i < this->atoms_per_mol; atom_i++) {
                    atom_counter_j = mol_j * atoms_per_mol;
                    for (atom_j = 0; atom_j < this->atoms_per_mol; atom_j++) {
                        atom_j_vec = traj.GetXYZ(frame, group, atom_counter_j);
                        atom_counter_j++;
                        r2 = distance2(*atom_i_vec.at(atom_i), *atom_j_vec, *box);

                        if (r2 < rcut2) {
                            add(c_i, c_j);
                            goto nextmol;
                        }
                    }
                }
            }

nextmol:
            continue;
        }
    }

    return;
}

/* This version is for when all atoms in a Trajectory object are used, so no
 * group name will be specified. */
void Clusters::do_clustering(int frame, Trajectory &traj, double rcut2)
{
    coordinates *atom_j_vec;
    double r2;
    int atom_counter_i;
    int atom_counter_j;
    int atom_i;
    int atom_j;
    int mol_i;
    int mol_j;
    int c_i;
    int c_j;
    triclinicbox* box;

    vector <coordinates*> atom_i_vec(atoms_per_mol);

    box = traj.GetBox(frame);
    initialize();

    for (mol_i = 0; mol_i < this->mol_n; mol_i++) {
        c_i = this->index.at(mol_i);

        /* Go ahead and save the atoms from this molecule to a vector so that we
         * don't have to keep accessing it later below. */
        atom_counter_i = mol_i * atoms_per_mol;
        for (atom_i = 0; atom_i < this->atoms_per_mol; atom_i++) {
            atom_i_vec.at(atom_i) = traj.GetXYZ(frame, atom_counter_i);
            atom_counter_i++;
        }

        for (mol_j = 0; mol_j < this->mol_n; mol_j++) {
            c_j = this->index.at(mol_j);

            if (c_i != c_j) {
                /* This compares every atom on the two molecules. If one pair is
                 * within the cutoff range then the two molecules should be
                 * added to the same cluster and no more checking is necessary
                 * for these two molecules. */
                for (atom_i = 0; atom_i < this->atoms_per_mol; atom_i++) {
                    atom_counter_j = mol_j * atoms_per_mol;
                    for (atom_j = 0; atom_j < this->atoms_per_mol; atom_j++) {
                        atom_j_vec = traj.GetXYZ(frame, atom_counter_j);
                        atom_counter_j++;
                        r2 = distance2(*atom_i_vec.at(atom_i), *atom_j_vec, *box);

                        if (r2 < rcut2) {
                            add(c_i, c_j);
                            goto nextmol;
                        }
                    }
                }
            }

nextmol:
            continue;
        }
    }

    return;
}
