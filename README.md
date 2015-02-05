This is a small library used for reading in Gromacs files (.xtc and .ndx) for
use in analyzing the results. This basically interfaces with libxdrfile and
implements an object-oriented style. The main usage of the library is to be able
to create a Trajectory object which reads in an XTC file along with an optional
GROMACS index file. This greatly simplifies writing an analysis program so that
code does not have to be rewritten every time one wants to do analysis. After
reading in the files the programmer can then use the Trajectory object's getter
functions to get the information desired for analysis.

#Requirements

Cmake and [libxdrfile](ftp://ftp.gromacs.org/pub/contrib/xdrfile-1.1.1.tar.gz) are required.

[Full documentation is located here.](http://wesbarnett.github.io/libgmxcpp)

#Installation

````
git clone git@github.com:wesbarnett/libgmxcpp.git
cd libgmxcpp
mkdir build
cd build
cmake ..
make
make install
````

#Example Program
There is an example program in the "example" directory. Use "make" to compile it
and test it out.
