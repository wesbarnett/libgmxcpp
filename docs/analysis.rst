Analysis Functions
==================

In addition to being able to read in trajectories and index files, some basic
analysis functions are included in the API. These are not intended to be
exhaustive of all possible analytical tools. Instead, this is a simple framework
the analyst can use in writing his own programs. All of these are currently
found in "gmxcpp/Utils.h", except for the clustering routines, which are found
in "gmxcpp/Clusters.h".

Bond vector
-----------
.. doxygenfunction:: bond_vector

Bond angle
----------
.. doxygenfunction:: bond_angle

Clustering
----------
.. doxygenclass:: Clusters

Cross product
-------------
.. doxygenfunction:: cross

Dihedral angle
--------------
.. doxygenfunction:: dihedral_angle

Distance
--------
.. doxygenfunction:: distance

Distance squared
----------------
.. doxygenfunction:: distance2

Dot product
-----------
.. doxygenfunction:: dot

Periodic boundary condition
---------------------------
.. doxygenfunction:: pbc

Random point on sphere
----------------------
.. doxygenfunction:: gen_sphere_point

Surface area
------------
.. doxygenfunction:: get_surf_area

Vector magnitude
----------------
.. doxygenfunction:: magnitude
