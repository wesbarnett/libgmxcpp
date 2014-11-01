#Installation

This is a small library used for reading in Gromacs files (.xtc and .ndx) for
use in analyzing the results. [libxdrfile](ftp://ftp.gromacs.org/pub/contrib/xdrfile-1.1.1.tar.gz) is required.

To install go into the src directory and do:

    make
    sudo make install

I'm assuming the xdrfile header files are in /usr/local/include/xdrfile. If not,
you'll have to modify the Makefile.

Check out the example program in the example directory. To compile it do:

    g++ main.cpp -I/usr/local/include/xdrfile -lgmxcpp -lxdrfile

Then you can run the program on an example xtc file and ndx file.

#Usage

[to do] See the example file for now as well as the comments in the source.
