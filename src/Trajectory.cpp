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

}

Trajectory::~Trajectory()
{
}

Trajectory::Trajectory(string filename, int b, int s, int e)
{
    init(filename, b, s, e);
}

Trajectory::Trajectory(string filename, string ndxfile, int b, int s, int e)
{
    Index index(ndxfile);
    this->index=index;
    init(filename, b, s, e);
}

Trajectory::Trajectory(string filename, Index index, int b, int s, int e)
{
    this->index=index;
    init(filename, b, s ,e);
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

void Trajectory::init(string filename, int b, int s, int e)
{
    int status = 0;
    this->count = 0;

    this->filename = filename;
    this->nframes = 0;

    try 
    {

        open(filename);

        printf("\nReading in xtc file...\n");;
        printf("Starting frame: %d\n", b);

        if (e == -1)
        {
            printf("Reading to the end of the file.\n");
        }
        else
        {
            printf("Ending frame: %d\n", e);
        }

        switch (s)
        {
            case 1:
                printf("Reading in every frame.\n");
                break;
            case 2:
                printf("Reading in every %dnd frame.\n", s);
                break;
            case 3:
                printf("Reading in every %drd frame.\n", s);
                break;
            default:
                printf("Reading in every %dth frame.\n", s);
                break;
        }

        if (e <= b && e != -1)
        {
            printf("NOTE: No frames being saved! Last frame comes before or is equal to first frame in Trajectory call!\n");
        }

        for (int i = 0; i < b; ++i)
        {
            status = skipFrame();
            if (status != 0)
            {
                break;
            }
            ++count;
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

            }
        }

        close();
    } 
    catch (runtime_error &excpt) 
    {
        cerr << endl << "Problem with creating Trajectory object." << endl;
        terminate();
    }
    return;
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
    printf("Opening xtc file %s...", filename.c_str());
    if (read_xtc_natoms(cfilename, &natoms) != 0)
    {
        throw runtime_error("Cannot open " + this->filename + ".");
    }
    printf("OK\n");
    printf("%d particles are in the system.\n", natoms);

    return;
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

    if (nframes % 10 == 0) 
    {
        printf("   frame in: %d", count);
        printf(" | time (ps): %f", time);
        printf(" | step: %d", step);
        printf(" | frame saved: %d\r", nframes);
    }

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

    if (nframes % 10 == 0) 
    {
        printf("   frame in: %d", count);
        printf(" | time (ps): %f", time);
        printf(" | step: %d", step);
        printf(" | frame saved: %d\r", nframes);
    }

    return 0;
}

void Trajectory::close()
{
    xdrfile_close(xd);
    printf("\nFinished reading in xtc file.\n");

    return;
}

// Gets the xyz coordinates when the frame and atom number are specified.
coordinates Trajectory::GetXYZ(int frame, int atom) const
{
    return frameArray[frame].GetXYZ(atom);
}

coordinates4 Trajectory::GetXYZ4(int frame, int atom) const
{
    return frameArray[frame].GetXYZ4(atom);
}

coordinates8 Trajectory::GetXYZ8(int frame, int atom) const
{
    return frameArray[frame].GetXYZ8(atom);
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

triclinicbox Trajectory::GetBox(int frame) const
{
    return frameArray[frame].GetBox();
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
