[![Documentation
Status](https://readthedocs.org/projects/libgmxcpp/badge/?version=master)](https://readthedocs.org/projects/libgmxcpp/?badge=master)

This is a C++ toolkit used for reading in GROMACS files (.xtc, .ndx, and .tpr) for
use in analyzing simulation results. This interfaces with libxdrfile and
implements an object-oriented style. The main usage of the library is to be able
to create a Trajectory object which reads in an XTC file along with an optional
GROMACS index file such that the user only has to worry with implementing the
actual analysis. Several functions which are repeatedly used in Molecular
Dynamics analysis (periodic boundary condition calculations, distances, etc.)
are also included. 

Versions 3.2.1 and above require GROMACS 5.1.

[Documentation is found here.](http://libgmxcpp.readthedocs.org/)

Copyright (C) 2015 James W. Barnett <jbarnet4@tulane.edu>
 
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.
 
This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 51
Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
The full license is located in a text file titled "LICENSE" in the root
directory of the source.
