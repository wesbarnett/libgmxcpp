[![Build Status](https://travis-ci.org/wesbarnett/libgmxcpp.svg?branch=releases)](https://travis-ci.org/wesbarnett/libgmxcpp)
[![Documentation
Status](https://readthedocs.org/projects/libgmxcpp/badge/?version=v3.2-rc1)](https://readthedocs.org/projects/libgmxcpp/?badge=v3.2-rc1)

This is a C++ toolkit used for reading in Gromacs files (.xtc and .ndx) for
use in analyzing simulation results. This interfaces with libxdrfile and
implements an object-oriented style. The main usage of the library is to be able
to create a Trajectory object which reads in an XTC file along with an optional
GROMACS index file such that the user only has to worry with implementing the
actual analysis. Several functions which are repeatedly used in Molecular
Dynamics analysis (periodic boundary condition calculations, distances, etc.)
are also included. 

[Documentation is found here.](http://libgmxcpp.readthedocs.org/)
