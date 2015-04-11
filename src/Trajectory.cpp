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

/**
 * @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 * @brief Trajectory class
 * @see Trajectory.h
 */

#include "gmxcpp/Trajectory.h"

// Initializes the trajectory object by finding out how many atoms are in the
// system, saving how many frames we think there might be for memory allocation. Then calls
// read().
Trajectory::Trajectory(string xtcfile, int maxFrames)
{
    cout << endl;
    try {
        InitXTC(xtcfile);
    } catch (runtime_error &excpt) {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
    read(maxFrames);
    return;
}

Trajectory::Trajectory(string filename)
{
    cout << endl;
    try {
        InitXTC(filename);
    } catch (runtime_error &excpt) {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
    read(MAXFRAMES);
    return;
}

Trajectory::Trajectory(string filename, string ndxfile)
{
    cout << endl;
    try {
        index.Set(ndxfile);
        InitXTC(filename);
    } catch (runtime_error &excpt) {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
    read(MAXFRAMES);
    return;
}

Trajectory::Trajectory(string filename, Index index)
{
    cout << endl;
    try {
        this->index=index;
        InitXTC(filename);
    } catch (runtime_error &excpt) {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
    read(MAXFRAMES);
    return;
}

Trajectory::Trajectory(string filename, string ndxfile, int initialFrames)
{
    try {
        InitXTC(filename);
        index.Set(ndxfile);
    } catch (runtime_error &excpt) {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
    read(initialFrames);
    return;
}


// Initializes the xtc file by opening the file and reading the number of atoms.
// We'll need that for read() later. read_xtc_natoms and xdrfile_open come from
// libxdrfile.
void Trajectory::InitXTC(string filename)
{
    char cfilename[200];

    for (unsigned int i = 0; i < filename.size(); i++)
        cfilename[i] = filename[i];
    cfilename[filename.size()] = '\0';
    xd = xdrfile_open(cfilename, "r");
    cout << "Opening xtc file " << filename << "...";
    if (read_xtc_natoms(cfilename, &natoms) != 0) throw runtime_error("Cannot open xtc file.");
    cout << "OK" << endl;
    nframes = 0;
    return;
}

// Reads in all of the frames from the xtc file. First, we resize frameArray to
// a it's initial size. Then we read in the xtc file frame by frame using
// libxdrfile's read_xtc function. We set the relevant data at each frame. If
// there are more frames left to read in but our vector wasn't large enough we
// warn the user (although we could do a resize, the user is allowed to choose a
// smaller number of frames and may not want them). Lastly we resize frameArray
// and close the xd file pointer from libxdrfile's xdrfile_close.
void Trajectory::read(int initialFrames)
{
    int status = 0;
    int step;
    matrix box;
    float time;
    rvec *x;

    frameArray.resize(initialFrames);

    cout << natoms << " particles are in the system." << endl;

    cout << "Allocated memory for " << initialFrames << " frames of data." << endl;
    cout << "Reading in xtc file: " << endl;
    while (status == 0 || nframes >= initialFrames) {
        x = new rvec[natoms];
        status = read_xtc(xd, natoms, &step, &time, box, x, &prec);
        if (nframes >= initialFrames) break;
        if (status != 0) break;
        frameArray.at(nframes).Set(step, time, box, x, natoms);
        if (nframes % 10 == 0) {
            cout << "   frame: " << nframes;
            cout << " | time (ps): " << time;
            cout << " | step: " << step << "\r";
        }
        nframes++;
    }

    if (nframes >= initialFrames) {
        cerr << "WARNING: More than " << initialFrames << " frames present in trajectory. Did not read all frames in." << endl;
        cerr << "See README.md for more info, under heading \'Construction\'." << endl;
    }

    cout << endl << "Read in " << nframes << " frames." << endl;
    frameArray.resize(nframes);

    status = xdrfile_close(xd);
    cout << "Finished reading in xtc file." << endl << endl;
    return;
}

// Gets the xyz coordinates when the frame and atom number are specified.
coordinates Trajectory::GetXYZ(int frame, int atom) const
{
    return frameArray.at(frame).GetXYZ(atom);
}

// Gets the xyz coordinates for the entire frame.
vector <coordinates> Trajectory::GetXYZ(int frame) const
{
    return frameArray.at(frame).GetXYZ();
}

// Gets the xyz coordinates for an entire group.
vector <coordinates> Trajectory::GetXYZ(int frame, string groupName) const
{
    return frameArray.at(frame).GetXYZ(index, groupName);
}


// Gets the xyz coordinates when the frame, group, and atom number are
// specified.
coordinates Trajectory::GetXYZ(int frame, string group, int atom) const
{
    int location = index.GetLocation(group, atom);

    return frameArray.at(frame).GetXYZ(location);
}

triclinicbox Trajectory::GetBox(int frame) const
{
    return frameArray.at(frame).GetBox();
}

int Trajectory::GetNAtoms(string group) const
{
    return index.GetGroupSize(group);
}

int Trajectory::GetNAtoms() const
{
    return natoms;
}

int Trajectory::GetNFrames() const
{
    return nframes;
}
float Trajectory::GetTime(int frame) const
{
    return frameArray.at(frame).GetTime();
}

int Trajectory::GetStep(int frame) const
{
    return frameArray.at(frame).GetStep();
}

double Trajectory::GetBoxVolume(int frame) const
{
    return frameArray.at(frame).GetBoxVolume();
}
