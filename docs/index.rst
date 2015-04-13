.. libgmxcpp documentation master file, created by
   sphinx-quickstart on Tue Apr  7 08:40:40 2015.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

libgmxcpp
=========

http://github.com/wesbarnett/libgmxcpp

This is a C++ toolkit used for reading in `Gromacs <http://www.gromacs.org/>`_
files (.xtc and .ndx) for use in analyzing simulation results. This interfaces
with libxdrfile and implements an object-oriented style. The main usage of the
library is to be able to create a Trajectory object which reads in an XTC file
along with an optional GROMACS index file such that the user only has to worry
with implementing the actual analysis. Several functions which are repeatedly
used in Molecular Dynamics analysis (periodic boundary condition calculations,
distances, etc.) are also included. 

Advantages
----------

* Only one object construction needs to be called to read in both .xtc and .ndx
  files.
* Index groups can be used by name within the program to get a desired atom's
  coordinates.
* Custom classes for atomic coordinates and simulation box allow overloading of
  operators to simplify coding.
* Common functions such as distance, magnitude, and cross product are built-in.
* Analysis loops can easily be parallelized with class getter functions, since
  all data frames are initially read in and can be accessed simultaneously.
* No other libraries needed (the relevant parts of libxdrfile are included with
  this project).

.. image:: images/screenshot.png

Development
-----------

The development branch is ``master``. Releases are merged into the ``release``
branch.


.. toctree::

   installation
   usage
   files
   analysis
   license
