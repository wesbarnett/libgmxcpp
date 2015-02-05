#libgmxcpp

This is a small library used for reading in Gromacs files (.xtc and .ndx) for
use in analyzing the results. This basically interfaces with libxdrfile and
implements an object-oriented style. The main usage of the library is to be able
to create a Trajectory object which reads in an XTC file along with an optional
GROMACS index file. 

##Advantages

* Only one object construction needs to be called to read in both .xtc and .ndx
  files.
* Index groups can be used by name within the program to get a desired atom's
  coordinates.
* Custom classes for atomic coordinates and simulation box allow overloading of
  operators to simplify coding.
* Common functions such as distance, magnitude, and cross product are built-in.
* Analysis loops can easily be parallelized with class getter functions, since
  all data frames are initially read in and can be accessed simultaneously.

[Full documentation is located here.](http://wesbarnett.github.io/libgmxcpp)

##Requirements

Cmake and [libxdrfile](ftp://ftp.gromacs.org/pub/contrib/xdrfile-1.1.1.tar.gz) are required.

##Installation

````
git clone git@github.com:wesbarnett/libgmxcpp.git
cd libgmxcpp
mkdir build
cd build
cmake ..
make
make install
````

##Example Program
There is an example program in the "example" directory. Use "make" to compile it
and test it out.

##Usage

See the example file as well as the comments in the source, especially
Trajectory.

The main idea is that you create a Trajectory object which contains all the
information from both the .xtc file (and optionally .ndx file). Trajectory
object methods are then used for analyzing the data.

###Construction

First, you should create a Trajectory object:

````c++
// Creates a Trajectory object with "traj.xtc" and "index.ndx"
// The index file is optional
// Both arguments are C++ strings
Trajectory traj("traj.xtc","index.ndx");
````

You could also make it a pointer:

````c++
Trajectory *traj = new Trajectory("traj.xtc","index.ndx");
````

In that case just remember to use "->" instead of "." when calling its methods.

Upon construction of a Trajectory object both the xtc file and the index file
are read into memory. The following sections detail how to access the data.

Additionally, one thing to consider is that the object initially allocates
enough memory for 100,000 frames and then reduces that to the correct amount of
frames read in. If you have more frames than that to read in, or you memory is
precious and you want to initially allocate for less, you can pass the number of
initial frames as a parameter in the construction:

````c++
// 2 million frames! With an index file.
Trajectory traj("traj.xtc","index.ndx",2000000);
// Without an index file
Trajectory traj("traj.xtc",2000000);
````

###Atomic Coordinates

To get the coordinates of an atom use GetXYZ() method. There are several
different options. Note that coordinates is simply a vector with double
precision. triclinicbox is a two dimensional vector with double precision.

You can get the coordinates for every atom in the system for a specific frame.

````c++
// For the 3rd frame
vector <coordinates> a = traj.GetXYZ(2);
// To print out the first atom's coordinates in this vector:
cout << a.at(0);
````

You can get the coordinates for every atom in an index group for a specific

````c++
// For group "C" in the 3rd frame
vector <coordinates> a = traj.GetXYZ(2,"C")
````

You can get the coordinates for one specific atom in the system for a specific
frame:

````c++
// Second atom in the 3rd frame
coordinates a = traj.GetXYZ(2,1);
// You can print cleanly:
cout << a;
````

You can get the coordinates for one specific atom in an index group for a frame:

````c++
// 2nd atom in group "C" in the 3rd frame
coordinates a = traj.GetXYZ(2,"C",1);
````

Usually you'll throw GetXYZ in a couple of loops to access the data you need.

###Box Dimensions

To get the box dimensions use GetBox() method:

````c++
// Gets the box dimensions from the first frame:
triclinicbox box = traj.GetBox(0);
// You can print cleanly:
cout << box;
````

###Box Volume

To get the volume of the simulation box for any frame:

````c++
// For frame 0
double vol = traj.GetBoxVolume(0);
````

###Number of Frames

To get the number of frames in the simulation use GetNFrames():

````c++
int nframes = traj.GetNFrames();
````

###Number of Atoms

To get the number of atoms in the entire system use GetNAtoms():

````c++
int natoms = traj.GetNAtoms();
````

To get the size (number of atoms in) a specific group pass the index name as an
argument:

````c++
// Gets the number of atoms in group "SOL"
int solsize = traj.GetNAtoms("SOL"):
````

###Time and Step

To get the time (in ps) corresponding with a frame use GetTime(frame):

````c++
// Gets the time of the 5th frame
float time = traj.GetTime(4);
````

To get the step for a frame use GetStep(frame):
````c++
// Gets the step corresponding with the 5th frame
int step = traj.GetStep(4);
````

###Utilities

Be sure to check out Utils.h which includes utilies in calculating atomic
distances, the periodic boundary condition, and more.
