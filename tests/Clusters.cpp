#include <assert.h>
#include "tests.h"
#include "gmxcpp/Clusters.h"
#include <iostream>
using namespace std;

int main()
{
    /* Test the clustering routines*/
	Trajectory traj("tests/clustertest.xtc","tests/clustertest.ndx");
	Clusters clust(4,4);

	clust.do_clustering(0,traj,"Site",pow(3.00,2));

	assert(clust.get_size(0)==4);
	for (int i = 1; i < 4; i++)
	{
		assert(clust.get_size(i)==0);
	}

	for (int i = 0; i < 4; i++)
	{
		assert(clust.get_index(i)==0);
	}

	clust.do_clustering(0,traj,"Site",pow(1.00,2));
	assert(clust.get_size(0)==2);
	assert(clust.get_size(1)==0);
	assert(clust.get_size(2)==1);
	assert(clust.get_size(3)==1);
	assert(clust.get_index(0)==0);
	assert(clust.get_index(1)==0);
	assert(clust.get_index(2)==2);
	assert(clust.get_index(3)==3);

    return 0;
}
