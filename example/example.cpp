/*
 * libgmxcpp
 * Copyright (C) 2015 James W. Barnett <jbarnet4@tulane.edu>
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * The full license is located in a text file titled "LICENSE" in the root
 * directory of the source.
 *
 */

/** @file
 * @brief Example program for use with libgmxcpp.
 *
 * @details This program shows how a Trajectory object can be creating, and then, as an
 * example the programmer is able to easily get all information from the
 * simulation. In this example the time, step, coordinates, and box size are
 * retrieved from the Trajectory object and are printed for the group "C" for
 * frames 0 up to 5 (this can be changed below, since your simulation might not
 * have that group). Most commands of interest in this program are in the
 * "print" function below.
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include "gmxcpp/Utils.h"

// This header file is required for creating a Trajectory object
#include "gmxcpp/Trajectory.h"

using namespace std;

void print(Trajectory *traj, int first, int last, string group, string outfile);
void printUsage(string program);

/** Parses the command line, then prints data to standard out */
int main(int argc, char *argv[])
{
    const string group = "OW"; // Water oxygen - change to suit your simulation
    const int first = 0;
    const int last = 5;
    string outfile = "out.dat";
    if (argc != 3) {printUsage(argv[0]); return -1;};
    string xtcfile = argv[1];
    string ndxfile = argv[2];

    // Example of creating a Trajectory object as a pointer
    Trajectory *traj = new Trajectory(xtcfile, ndxfile);

    // Only reading in from frame first to last
    traj->read(first, 1, last);

    print(traj, first, last, group, outfile);

    return 0;
}

/**
 * @brief Parses the command line.
 * @details Parses the command line, getting the xtc file and index file names.
 * Also checks if help flag is initiated.
 * @param xtcfile Name of XTC file
 * @param ndxfile Name of the index file
 * @param argc Number of command line paramters
 * @param argv[] Command line parameter
 * @return True If there is no error or help flag not called. Otherwise false.
 */

/**
 * @brief Prints the usage of the program.
 * @param program Name of program from command line.
 */
void printUsage(string program)
{
    cout << endl;
    cout << "Usage:" << endl;
    cout << "  " << program << " traj.xtc index.ndx" << endl;
    cout << "Arguments:" << endl;
    cout << "   traj.xtc  (Input, Gromacs xtc file)" << endl;
    cout << "   index.ndx (Input, Gromacs index file)" << endl;
    cout << endl;
    return;
}

/**
 * @brief Prints example info from the Trajectory.
 * @param traj Pointer to the Trajectory object.
 * @param first First frame to print.
 * @param last Last frame to print.
 * @param group Specific index group to print.
 * @param outfile File to which to print.
 */
void print(Trajectory *traj, int first, int last, string group, string outfile)
{
    ofstream oFS;

    oFS.open(outfile.c_str());
    vector <coordinates> xyz;
    triclinicbox box;

    cout << "Writing example data to " << outfile << "." << endl;

    if (!oFS.is_open()) {
        cout << "ERROR: Cannot open output file." << endl;
        return;
    }

    oFS << fixed << setprecision(3);

    for (int frame = first; frame < last; frame++) {
        oFS << "------------------------------------" << endl;

        // Getting and printing the time and step
        oFS << "Time: " << traj->GetTime(frame) << " ps" << endl;
        oFS << "Step: " << traj->GetStep(frame) << endl;

        oFS << endl;

        // Getting all of the coordinates for this frame for this groupand printing them
        oFS << "Coordinates for group " << group << ":" << endl;
        xyz = traj->GetXYZ(frame, group);
        for (int i = 0; i < traj->GetNAtoms(group); i++)
            oFS << xyz.at(i);


        oFS << endl;

        // Getting and printing the box coordinates for this frame
        oFS << "Box: " << endl;
        box = traj->GetBox(frame);
        oFS << box;

        oFS << "Box volume: " << endl;
        oFS << traj->GetBoxVolume(frame) << endl;
    }

    oFS.close();

    return;
}
