#ifndef UNCERTAINTY_H
#define UNCERTAINTY_H

#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

/*
 * The following "bootstrap" functions split up a set of data ("data") into
 * several blocks. These blocks are randomly chosen with replacement. The
 * values corresponding with these blocks are then calculated. For these
 * calculations the data is a value averaged over the entirety of a simulation.
 * The new values are calculated boot_n times and stored into a vector. Then the
 * variance of these new values are calculated. The square root of that is the
 * uncertainty. The first of these functions is for a set of data (so a
 * two-dimensional vector). The second function is for a single value.
 */

vector <double> bootstrap(int boot_n, int block_n, vector < vector <double> >& data, int frame_count);
double bootstrap(int boot_n, int block_n, vector <double> & data, int frame_count);
vector <double> get_boot_values(int block_n, vector < vector <double> >& data, int frame_count);
vector <double> get_uncertainty(int boot_n, int data_size, vector <double>&avg, vector < vector <double> >& values);

#endif
