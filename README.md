##About

This is a small library used for reading in Gromacs files (.xtc and .ndx) for
use in analyzing the results. [libxdrfile] (ftp://ftp.gromacs.org/pub/contrib/xdrfile-1.1.1.tar.gz) is required. This basically takes a few of the xdrfile routines and makes them object-oriented.

##Installation

To install do:

    git clone git@github.com:wesbarnett/libgmxcpp.git
    cd libgmxcpp/src
    make
    sudo make install

I'm assuming the xdrfile header files are in /usr/local/include/xdrfile. If not,
you'll have to modify the Makefile.

Check out the example program in the example directory. To compile it do:

    g++ main.cpp -I/usr/local/include/xdrfile -lgmxcpp -lxdrfile

Then you can run the program on an example xtc file and ndx file.

##Usage

See the example file as well as the comments in the source. 

The main idea is that you create a Trajectory object which contains all the
information from both the .xtc file (and optionally .ndx file). Trajectory
object methods are then used for analyzing the data.

To create a Trajectory object with "traj.xtc" and "index.ndx":

    Trajectory traj("traj.xtc","index.ndx");

You could also make it a pointer:

    Trajectory *traj = new Trajectory("traj.xtc","index.ndx");

In that case just remember to use "->" instead of "." when calling its methods.

To get the coordinates of the 2nd atom of the 3rd frame of index group "C" and
store in three dimensional vector a.

    rvec a;
    traj.GetXYZ(2,"C",1,a);

Frame is specified, then group name, then atom number in that group. Lastly, the
rvec variable where the coordinates are stored is specified.

To print out the coordinates you would then do:

    cout << a[X] << " " << a[Y] << " " << a[Z] << endl;

X, Y, and Z are constants specified in Trajectory.h, equal to 0, 1, and 2
respectively.

You can omit the group name from the call:

    traj.GetXYZ(2,1,a);

Now the variable a contains the coordinates of the 2nd atom in the 3rd frame of
the simulation.

To get the box dimensions for the first frame do:

    matrix box;
    traj.GetBox(0,box);

matrix is a three by three array.

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
