Analysis Functions
==================

In addition to being able to read in trajectories and index files, some basic
analysis functions are included in the API. These are not intended to be
exhaustive of all possible analytical tools. Instead, this is a simple framework
the analyst can use in writing his own programs. All of these are currently
<<<<<<< HEAD
found in "gmxcpp/Utils.h", except for the clustering routines, which are found
in "gmxcpp/Clusters.h".
=======
found in ``gmxcpp/Utils.h``, except for the clustering routines, which are found
in ``gmxcpp/Clusters.h``.
>>>>>>> master

Bond vector
-----------
.. doxygenfunction:: bond_vector

Bond angle
----------
.. doxygenfunction:: bond_angle

<<<<<<< HEAD
=======
Center a group of atoms around a point
-------------------------------------
.. doxygenfunction:: do_center_group

Center of mass
--------------
.. doxygengroup:: center_of_mass

>>>>>>> master
Clustering
----------
.. doxygenclass:: Clusters
    :members:

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

<<<<<<< HEAD
=======
Geometric center
----------------
.. doxygenfunction:: center_of_geometry

>>>>>>> master
Periodic boundary condition
---------------------------
.. doxygenfunction:: pbc

Random point on sphere
----------------------
<<<<<<< HEAD
.. doxygenfunction:: gen_sphere_point
=======
.. doxygengroup:: gen_sphere_point
>>>>>>> master

Surface area
------------
.. doxygenfunction:: get_surf_area

Vector magnitude
----------------
.. doxygenfunction:: magnitude
