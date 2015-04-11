Reading in Files
================

.. highlight:: cpp

The basic idea of the library is two-fold and contains two main aspects: 1)
Reading in Gromacs files into memory using constructors and using getters to
access their information in an analysis program, and 2) a set of basic analysis
functions (see next section). Currently libgmxcpp can read in .xtc, .ndx, and
.tpr files (tpr files are limited currently to mass and charge).  The three
classes that correspond to these file formats are listed below. Each class
contains its own header file in
the `gmxcpp` directory.

Index
-----
.. doxygenclass:: Index
    :members:

Topology
----------
.. doxygenclass:: Topology
    :members:

Trajectory
----------
.. doxygenclass:: Trajectory
    :members:

