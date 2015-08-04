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


Trajectory::Trajectory(string filename)
{
    init(filename);
}

Trajectory::Trajectory(string filename, string ndxfile)
{
    Index index(ndxfile);
    this->index=index;
    init(filename);
}

Trajectory::Trajectory(string filename, Index index)
{
    this->index=index;
    init(filename);
}

// Initializes the trajectory object by finding out how many atoms are in the
// system, saving how many frames we think there might be for memory allocation.
// Reads in all of the frames from the xtc file. First, we resize frameArray to
// a it's initial size. Then we read in the xtc file frame by frame using
// libxdrfile's read_xtc function. We set the relevant data at each frame. If
// there are more frames left to read in but our vector wasn't large enough we
// warn the user (although we could do a resize, the user is allowed to choose a
// smaller number of frames and may not want them). Lastly we resize frameArray
// and close the xd file pointer from libxdrfile's xdrfile_close.

void Trajectory::init(string filename)
{
    int status = 0;
    int step;
    matrix box;
    float time;
    Frame frame;
    rvec *x;
    char cfilename[200];
    cout << endl;

    try 
    {
        this->nframes = 0;

        for (unsigned int i = 0; i < filename.size(); i++)
        {
            cfilename[i] = filename[i];
        }
        cfilename[filename.size()] = '\0';
        xd = xdrfile_open(cfilename, "r");
        cout << "Opening xtc file " << filename << "...";
        if (read_xtc_natoms(cfilename, &natoms) != 0)
        {
            throw runtime_error("Cannot open xtc file.");
        }
        cout << "OK" << endl;

        cout << natoms << " particles are in the system." << endl;

        cout << "Reading in xtc file: " << endl;

        while (status == 0) 
        {
            x = new rvec[natoms];
            status = read_xtc(xd, natoms, &step, &time, box, x, &prec);
            if (status != 0) 
            {
                break;
            }
            frame = Frame(step, time, box, x, natoms);
            frameArray.push_back(frame);
            if (nframes % 10 == 0) 
            {
                cout << "   frame: " << nframes;
                cout << " | time (ps): " << time;
                cout << " | step: " << step << "\r";
            }
            nframes++;
        }

        status = xdrfile_close(xd);
        cout << endl << "Finished reading in xtc file." << endl << endl;
    } 
    catch (runtime_error &excpt) 
    {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
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
