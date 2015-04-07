Basic Usage
===========

.. highlight:: cpp

See the example file as well as the comments in the source, especially
Trajectory.

The main idea is that you create a Trajectory object which contains all the
information from both the .xtc file (and optionally .ndx file). Trajectory
object methods are then used for analyzing the data.

###Construction

First, you should create a Trajectory object:::

    // Creates a Trajectory object with "traj.xtc" and "index.ndx"
    // The index file is optional
    // Both arguments are C++ strings
    Trajectory traj("traj.xtc","index.ndx");

You could also make it a pointer:::

    Trajectory *traj = new Trajectory("traj.xtc","index.ndx");

In that case just remember to use "->" instead of "." when calling its methods.

Upon construction of a Trajectory object both the xtc file and the index file
are read into memory. The following sections detail how to access the data.

Additionally, one thing to consider is that the object initially allocates
enough memory for 100,000 frames and then reduces that to the correct amount of
frames read in. If you have more frames than that to read in, or you memory is
precious and you want to initially allocate for less, you can pass the number of
initial frames as a parameter in the construction:::

    // 2 million frames! With an index file.
    Trajectory traj("traj.xtc","index.ndx",2000000);
    // Without an index file
    Trajectory traj("traj.xtc",2000000);

###Atomic Coordinates

To get the coordinates of an atom use GetXYZ() method. There are several
different options. Note that coordinates is simply a vector with double
precision. triclinicbox is a two dimensional vector with double precision.

You can get the coordinates for every atom in the system for a specific frame.::

    // For the 3rd frame
    vector <coordinates> a = traj.GetXYZ(2);
    // To print out the first atom's coordinates in this vector:
    cout << a.at(0);

You can get the coordinates for every atom in an index group for a specific::

    // For group "C" in the 3rd frame
    vector <coordinates> a = traj.GetXYZ(2,"C")

You can get the coordinates for one specific atom in the system for a specific
frame:::

    // Second atom in the 3rd frame
    coordinates a = traj.GetXYZ(2,1);
    // You can print cleanly:
    cout << a;

You can get the coordinates for one specific atom in an index group for a
frame:::

    // 2nd atom in group "C" in the 3rd frame
    coordinates a = traj.GetXYZ(2,"C",1);

Usually you'll throw GetXYZ in a couple of loops to access the data you need.

###Box Dimensions

To get the box dimensions use GetBox() method:::

    // Gets the box dimensions from the first frame:
    triclinicbox box = traj.GetBox(0);
    // You can print cleanly:
    cout << box;

###Box Volume

To get the volume of the simulation box for any frame:::

    // For frame 0
    double vol = traj.GetBoxVolume(0);

###Number of Frames

To get the number of frames in the simulation use GetNFrames():::

    int nframes = traj.GetNFrames();

###Number of Atoms

To get the number of atoms in the entire system use GetNAtoms():::

    int natoms = traj.GetNAtoms();

To get the size (number of atoms in) a specific group pass the index name as an
argument:::

    // Gets the number of atoms in group "SOL"
    int solsize = traj.GetNAtoms("SOL"):

###Time and Step

To get the time (in ps) corresponding with a frame use GetTime(frame):::

    // Gets the time of the 5th frame
    float time = traj.GetTime(4);

To get the step for a frame use GetStep(frame):::

    // Gets the step corresponding with the 5th frame
    int step = traj.GetStep(4);

###Utilities

Be sure to check out Utils.h which includes utilies in calculating atomic
distances, the periodic boundary condition, and more.

