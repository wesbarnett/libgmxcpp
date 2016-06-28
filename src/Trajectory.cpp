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

Trajectory::Trajectory()
{
    PrintBanner();
}

Trajectory::~Trajectory()
{
}

Trajectory::Trajectory(string filename)
{
    PrintBanner();
    this->filename = filename;
    open(filename);
}

Trajectory::Trajectory(string filename, string ndxfile)
{
    PrintBanner();
    Index index(ndxfile);
    this->index=index;
    this->filename = filename;
    open(filename);
}

Trajectory::Trajectory(string filename, Index index)
{
    PrintBanner();
    this->index=index;
    this->filename = filename;
    open(filename);
}

/*
 * Initializes the trajectory object by finding out how many atoms are in the
 * system, saving how many frames we think there might be for memory allocation.
 * Reads in all of the frames from the xtc file. First, we resize frameArray to
 * a it's initial size. Then we read in the xtc file frame by frame using
 * libxdrfile's read_xtc function. We set the relevant data at each frame. If
 * there are more frames left to read in but our vector wasn't large enough we
 * warn the user (although we could do a resize, the user is allowed to choose a
 * smaller number of frames and may not want them). Lastly we resize frameArray
 * and close the xd file pointer from libxdrfile's xdrfile_close.
 */

int Trajectory::read(int b, int s, int e)
{
    int status = 0;
    this->count = 0;

    this->nframes = 0;

    cout << endl;

    try 
    {

        open(filename);

        cout << "Reading in xtc file: " << endl;
        cout << "Starting frame: " << b << endl;

        if (e == -1)
        {
            cout << "Reading to the end of the file." << endl;
        }
        else
        {
            cout << "Ending frame: " << e << endl;
        }

        if (s == 1)
        {
            cout << "Reading in every frame." << endl;
        }
        else if (s == 2)
        {
            cout << "Reading in every " << s << "nd frame." << endl;
        }
        else if (s == 3)
        { 
            cout << "Reading in every " << s << "rd frame." << endl;
        }
        else if (s >= 4)
        {
            cout << "Reading in every " << s << "th frame." << endl;
        }

        if (e <= b && e != -1)
        {
            cout << "NOTE: No frames being saved! Last frame comes before or is equal to first frame in Trajectory call!" << endl;
        }

        for (int i = 0; i < b; ++i)
        {
            status = skipFrame();
            if (status != 0)
            {
                break;
            }
            ++count;
            printInfo();
        }

        if (e == -1)
        {
            while (status == 0) 
            {
                if (count % s == 0)
                {
                    status = readFrame();
                }
                else
                {
                    status = skipFrame();
                }
                ++count;
                printInfo();
            }
        }
        else
        {
            while (status == 0) 
            {
                if (count % s == 0)
                {
                    status = readFrame();
                }
                else
                {
                    status = skipFrame();
                }
                ++count;

                if (count >= e)
                {
                    break;
                }
                printInfo();

            }
        }

        close();
    } 
    catch (runtime_error &excpt) 
    {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
    return nframes;
}

void Trajectory::open(string filename)
{
    char cfilename[200];

    for (unsigned int i = 0; i < filename.size(); ++i)
    {
        cfilename[i] = filename[i];
    }
    cfilename[filename.size()] = '\0';
    xd = xdrfile_open(cfilename, "r");
    cout << "Opening xtc file " << filename << "...";
    if (read_xtc_natoms(cfilename, &natoms) != 0)
    {
        throw runtime_error("Cannot open " + this->filename + ".");
    }
    cout << "OK" << endl;
    cout << natoms << " particles are in the system." << endl;

    return;
}

int Trajectory::read_next(int n)
{
    frameArray.clear();
    frameArray.reserve(n);
    nframes = 0;
    int status;
    for (int i = 0; i < n; i++)
    {
        status = readFrame();
        if (status != 0)
        {
            break;
        }
    }
    return nframes;
}

int Trajectory::readFrame()
{
    float time;
    float prec;
    int status;
    int step;
    matrix box;
    rvec *x;

    x = new rvec[natoms];
    status = read_xtc(xd, natoms, &step, &time, box, x, &prec);

    if (status != 0) 
    {
        return -1;
    }

    frameArray.push_back(Frame(step, time, box, x, natoms));

    ++nframes;

    return 0;
}



int Trajectory::skipFrame()
{
    float time;
    float prec;
    int status;
    int step;
    matrix box;
    rvec *x;

    x = new rvec[natoms];
    status = read_xtc(xd, natoms, &step, &time, box, x, &prec);

    if (status != 0) 
    {
        return -1;
    }

    return 0;
}

void Trajectory::printInfo()
{
    if (nframes % 10 == 0) 
    {
        cout << "   frame in: " << count;
        cout << " | frame saved: " << nframes << "\r";
    }
    return;
}

void Trajectory::close()
{
    xdrfile_close(xd);
    cout << endl << "Finished reading in xtc file." << endl << endl;

    return;
}

// Gets the xyz coordinates when the frame and atom number are specified.
coordinates Trajectory::GetXYZ(int frame, int atom) const
{
    return frameArray[frame].GetXYZ(atom);
}

// Gets the xyz coordinates for the entire frame.
vector <coordinates> Trajectory::GetXYZ(int frame) const
{
    return frameArray[frame].GetXYZ();
}

// Gets the xyz coordinates for an entire group.
vector <coordinates> Trajectory::GetXYZ(int frame, string groupName) const
{
    return frameArray[frame].GetXYZ(index, groupName);
}

// Gets the xyz coordinates when the frame, group, and atom number are
// specified.
coordinates Trajectory::GetXYZ(int frame, string group, int atom) const
{
    return frameArray[frame].GetXYZ(index.GetLocation(group, atom));
}

triclinicbox Trajectory::GetBox(int frame) const
{
    return frameArray[frame].GetBox();
}

cubicbox Trajectory::GetCubicBox(int frame) const
{
    return frameArray[frame].GetCubicBox();
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
    return frameArray[frame].GetTime();
}

int Trajectory::GetStep(int frame) const
{
    return frameArray[frame].GetStep();
}

double Trajectory::GetBoxVolume(int frame) const
{
    return frameArray[frame].GetBoxVolume();
}

string Trajectory::GetFilename() const
{   
    return this->filename;
}

void Trajectory::CenterAtoms(int frame) const
{
    frameArray[frame].CenterAtoms();
    return;
}

void Trajectory::PrintBanner() const
{
#ifdef BANNER
    cerr << endl;
    cerr << "===========================================================" << endl;
    cerr << "=  libgmxcpp v5.0 -- Copyright (C) 2016 James W. Barnett  =" << endl;
    cerr << "=  http://github.com/wesbarnett/libgmxcpp                 =" << endl;
    cerr << "===========================================================" << endl;
    cerr << endl;
#endif
    return;
}

#ifdef AVX

coordinates4 Trajectory::GetXYZ4(int frame, int atom) const
{
    return frameArray[frame].GetXYZ4(atom);
}

coordinates8 Trajectory::GetXYZ8(int frame, int atom) const
{
    return frameArray[frame].GetXYZ8(atom);
}

coordinates8 Trajectory::GetXYZ8F(int frame, int atom) const
{
    return  (coordinates8 (frameArray[frame].GetXYZ(atom),
                           frameArray[frame+1].GetXYZ(atom),
                           frameArray[frame+2].GetXYZ(atom),
                           frameArray[frame+3].GetXYZ(atom),
                           frameArray[frame+4].GetXYZ(atom),
                           frameArray[frame+5].GetXYZ(atom),
                           frameArray[frame+6].GetXYZ(atom),
                           frameArray[frame+7].GetXYZ(atom)) );
}

coordinates4 Trajectory::GetXYZ4(int frame, string group, int atom) const
{
    return frameArray[frame].GetXYZ4(index.GetLocation(group, atom),
                                     index.GetLocation(group, atom+1),
                                     index.GetLocation(group, atom+2),
                                     index.GetLocation(group, atom+3));
}

coordinates8 Trajectory::GetXYZ8(int frame, string group, int atom) const
{
    return frameArray[frame].GetXYZ8(index.GetLocation(group, atom),
                                     index.GetLocation(group, atom+1),
                                     index.GetLocation(group, atom+2),
                                     index.GetLocation(group, atom+3),
                                     index.GetLocation(group, atom+4),
                                     index.GetLocation(group, atom+5),
                                     index.GetLocation(group, atom+6),
                                     index.GetLocation(group, atom+7));
}

coordinates8 Trajectory::GetXYZ8F(int frame, string group, int atom) const
{
    return ( coordinates8 (frameArray[frame].GetXYZ(index.GetLocation(group, atom)),
                           frameArray[frame+1].GetXYZ(index.GetLocation(group, atom)),
                           frameArray[frame+2].GetXYZ(index.GetLocation(group, atom)),
                           frameArray[frame+3].GetXYZ(index.GetLocation(group, atom)),
                           frameArray[frame+4].GetXYZ(index.GetLocation(group, atom)),
                           frameArray[frame+5].GetXYZ(index.GetLocation(group, atom)),
                           frameArray[frame+6].GetXYZ(index.GetLocation(group, atom)),
                           frameArray[frame+7].GetXYZ(index.GetLocation(group, atom))) );

}

cubicbox_m256 Trajectory::GetCubicBoxM256(int frame) const
{
    return frameArray[frame].GetCubicBoxM256();
}

cubicbox8 Trajectory::GetCubicBox8F(int frame) const
{
    return ( cubicbox8 (frameArray[frame].GetCubicBox(),
                        frameArray[frame+1].GetCubicBox(),
                        frameArray[frame+2].GetCubicBox(),
                        frameArray[frame+3].GetCubicBox(),
                        frameArray[frame+4].GetCubicBox(),
                        frameArray[frame+5].GetCubicBox(),
                        frameArray[frame+6].GetCubicBox(),
                        frameArray[frame+7].GetCubicBox()) );
}
#endif
