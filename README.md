##libgmxcpp

This is a small library used for reading in Gromacs files (.xtc and .ndx) for
use in analyzing the results. The [libxdrfile](ftp://ftp.gromacs.org/pub/contrib/xdrfile-1.1.1.tar.gz) library is required. This basically interfaces with the xdrfile and implements an object-oriented style.

##Installation

To install do:

    git clone git@github.com:wesbarnett/libgmxcpp.git
    cd libgmxcpp/src
    make
    sudo make install

I'm assuming the xdrfile header files are in /usr/local/include/xdrfile. If not,
you'll have to modify the Makefile.

Check out the example program in the example directory. To compile it do:

    cd libgmxcpp/example
    make

Then you can run the program on an example xtc file and ndx file.

##Usage

See the example file as well as the comments in the source. 

The main idea is that you create a Trajectory object which contains all the
information from both the .xtc file (and optionally .ndx file). Trajectory
object methods are then used for analyzing the data.

To create a Trajectory object:

    // Creates a Trajectory object with "traj.xtc" and "index.ndx"
    // The index file is optional
    Trajectory traj("traj.xtc","index.ndx");

You could also make it a pointer:

    Trajectory *traj = new Trajectory("traj.xtc","index.ndx");

In that case just remember to use "->" instead of "." when calling its methods.

To get the coordinates of an atom use GetXYZ() method:

    rvec a; // rvec comes from xdrfile library and is a three dimensional float array
    // Gets the 2nd atom of the 3rd frame of index group "C"
    // Arguments are frame, group name, atom number, rvec variable with coordinates stored
    traj.GetXYZ(2,"C",1,a);

    // You can omit the group, getting the 2nd atom in the entire system
    traj.GetXYZ(2,1,a);

To print out the coordinates you would then do:

    // X, Y, and Z are constants in Utils.h, equiv. to 0, 1, and 2
    cout << a[X] << " " << a[Y] << " " << a[Z] << endl;

Now the variable a contains the coordinates of the 2nd atom in the 3rd frame of
the simulation.

To get the box dimensions use GetBox() method:

    matrix box; // matrix is a three by three float array from xdrfile library
    // Gets the box dimensions from the first frame:
    traj.GetBox(0,box);

To get the number of frames in the simulation:

    int nframes = traj.GetNFrames();

To get the number of atoms:

    int natoms = traj.GetNAtoms();

To get the size (number of atoms in) group "SOL":

    int solsize = traj.GetNAtoms("SOL"):

To get the time (in ps) corresponding with a frame (in this case the 5th frame)
do:

    float time = traj.GetTime(4);

To get the step for that frame:

    int step = traj.GetStep(4);
