
Example Workflow
================

Workflow
--------

This is a suggested workflow for using this library in constructing one's
analysis program. As an example this tutorial will walk through creating a
program that calculates the center of mass of a group of atoms from a Gromacs
simulation.

Let's say you have simulated several methanes in water. In the case of
calculating the center of mass of the methanes we'll need the .xtc file (having
the coordinates), the .ndx file (grouping the atoms), and the .tpr file (having
the masses).

The first thing to do is to construct an object associated for each file type.
First we'll read in the index file:::

    Index ndx("index.ndx");

Then we'll read in both the .xtc and .tpr files and associate the Index object
with it. This is optional, but we want to do it in this case since we can easily
find the methanes by our index groups:::

    Trajectory trj("traj.xtc",ndx);
    Topology top("topol.tpr",ndx);

Now all information from the simulation is available to us using object getters
from ``trj`` and ``top``. Since ``ndx`` is now associated with both of these
object we don't have to worry about calling anything from it directly.

UNDER CONSTRUCTION


Other Examples
--------------
There is an example program in the ``example`` directory. Use ``make`` to compile it
and test it out on an .xtc and .ndx file from a recent simulation.

Additionally `there is an example program which calculates the radial
distribution function using this library <https://github.com/wesbarnett/rdf>`_.
