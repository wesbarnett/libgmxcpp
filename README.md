# libgmxcpp

**NOTE**: Since I am no longer an active GROMACS user, this code may not be updated for future versions of GROMACS. Part of the library are known the be incompatible with GROMACS 2018+. If you are interested in keeping this project moving forward for future versions of GROMACS, please fork. The main incompatibility will be `Topology.cpp`. Other functionalities hopefully will not change much in the future for GROMACS.

[![DOI](https://zenodo.org/badge/26054161.svg)](https://zenodo.org/badge/latestdoi/26054161)

[![Documentation Status](https://readthedocs.org/projects/libgmxcpp/badge/?version=master)](http://libgmxcpp.readthedocs.io/en/master/)
[![License](https://img.shields.io/aur/license/libgmxcpp.svg)](https://github.com/wesbarnett/libgmxcpp/blob/master/LICENSE)
[![AUR
Version](https://img.shields.io/aur/version/libgmxcpp.svg)](https://aur.archlinux.org/packages/libgmxcpp/)
[![AUR
Votes](https://img.shields.io/aur/votes/libgmxcpp.svg)](https://aur.archlinux.org/packages/libgmxcpp/)

This is a C++ toolkit used for reading in GROMACS files (.xtc, .ndx, and .tpr) for
use in analyzing simulation results. This interfaces with libxdrfile and
implements an object-oriented style. The main usage of the library is to be able
to create a Trajectory object which reads in an XTC file along with an optional
GROMACS index file such that the user only has to worry with implementing the
actual analysis. Several functions which are repeatedly used in Molecular
Dynamics analysis (periodic boundary condition calculations, distances, etc.)
are also included. 

Copyright (C) 2016 James W. Barnett <libgmxcpp@wbarnett.us>

Latest documentation: http://libgmxcpp.readthedocs.io

Also [check out libgmxcpp's Fortran
cousin.](https://github.com/wesbarnett/libgmxfort)
