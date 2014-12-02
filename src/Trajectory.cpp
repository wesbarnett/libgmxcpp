
#include "Trajectory.h"

// Initializes the trajectory object by finding out how many atoms are in the 
// system, saving how many frames we think there might be for memory allocation. Then calls
// read().
Trajectory::Trajectory(string filename, int initialFrames) {
    cout << endl;
	try {
        InitXTC(filename);
	} catch(runtime_error &excpt) {
		cerr << endl << "Problem with creating Trajectory object." << endl;
		terminate();
	}
	read(initialFrames);
	return;
}

Trajectory::Trajectory(string filename) {
    cout << endl;
	try {
        InitXTC(filename);
	} catch(runtime_error &excpt) {
		cerr << endl << "Problem with creating Trajectory object." << endl;
		terminate();
	}
	read(100000);
	return;
}

Trajectory::Trajectory(string filename, string ndxfile) {
    cout << endl;
	try {
		index.Set(ndxfile);
        InitXTC(filename);
	} catch(runtime_error &excpt) {
		cerr << endl << "Problem with creating Trajectory object." << endl;
		terminate();
	}
	read(100000);
	return;
}

Trajectory::Trajectory(string filename, string ndxfile, int initialFrames) {
	try {
        InitXTC(filename);
		index.Set(ndxfile);
	} catch(runtime_error &excpt) {
		cerr << endl << "Problem with creating Trajectory object." << endl;
		terminate();
	}
	read(initialFrames);
	return;
}


void Trajectory::InitXTC(string filename) {
	char cfilename[200];
	for (int i=0;i<filename.size();i++) {
		cfilename[i] = filename[i];
	}
	cfilename[filename.size()] = '\0';
	xd = xdrfile_open(cfilename,"r");
	cout << "Opening xtc file " << filename << "...";
	if (read_xtc_natoms(cfilename,&natoms) != 0) throw runtime_error("Cannot open xtc file.");
	cout << "OK" << endl;
	nframes = 0;
    return;
}

// Reads in all of the frames from the xtc file. First, we allocate memory 
// for our temporary Frame array. Then we allocate memory for the vectors 
// for this frame based on the number of atoms read in from earlier. We 
// cycle through each frame, saving the important info for each step into 
// the temporary frame array. After this we allocate memory for the final 
// frame array based on how many frames were read in. Lastly, we delete the 
// temporary array.
void Trajectory::read(int initialFrames) {

	int status = 0;
	int step;
	matrix box;
	float time;
	rvec *x;
	int j = 0;
	frameArray.resize(initialFrames);

	cout << natoms << " particles are in the system." << endl;

	cout << "Allocated memory for " << initialFrames << " frames of data." << endl;
    cout << "Reading in xtc file: " << endl;
	while (status == 0) {
		x = new rvec[natoms];
		status = read_xtc(xd,natoms,&step,&time,box,x,&prec);
		if (status !=0) break;
		frameArray.at(nframes).Set(step,time,box,x);
		if (nframes % 10 == 0) {
            cout << "   frame: " << nframes;
            cout << " | time (ps): " << time;
            cout << " | step: " << step << "\r";
        }
		nframes++;
    }

	cout << endl << "Read in " << nframes << " frames." << endl;
	cout << "Freeing up memory..." << endl;
	frameArray.resize(nframes);

	status = xdrfile_close(xd);
	cout << "Finished reading in xtc file." << endl << endl;
	return;
}

// Gets the xyz coordinates when the frame and atom number are specified.
void Trajectory::GetXYZ(int frame, int atom, rvec xyz) const {
	frameArray.at(frame).GetXYZ(atom,xyz);
    return;
}

// Gets the xyz coordinates when the frame, group, and atom number are
// specified.
void Trajectory::GetXYZ(int frame, string group, int atom, rvec xyz) const {
	int location = index.GetLocation(group, atom);
	if (location == -1) return;
	frameArray.at(frame).GetXYZ(location,xyz);
    return;
}

void Trajectory::GetXYZ(string group, int frame, int atom, rvec xyz) const {
    this->GetXYZ(frame,group,atom,xyz);
    return;
}

// Gets all the coordinates for the entire frame
void Trajectory::GetXYZ(int frame, rvec xyz[]) const {
	frameArray.at(frame).GetXYZ(xyz,natoms);
    return;
}

// Gets all the coordinates for the entire frame for one group
void Trajectory::GetXYZ(int frame, string group, rvec xyz[]) const {
    frameArray.at(frame).GetXYZ(xyz,index,group);
    return;
}

// Gets the box dimensions for a specific frame
void Trajectory::GetBox(int frame, matrix box) const {
	frameArray.at(frame).GetBox(box);
	return;
}

int Trajectory::GetNAtoms(string group) const {
	return index.GetGroupSize(group);
}

int Trajectory::GetNAtoms() const {
    return natoms;
}

int Trajectory::GetNFrames() const {
	return nframes;
}
float Trajectory::GetTime(int frame) const {
	return frameArray.at(frame).GetTime();
}

int Trajectory::GetStep(int frame) const {
	return frameArray.at(frame).GetStep();
}

double Trajectory::GetBoxVolume(int frame) const {
	return frameArray.at(frame).GetBoxVolume();
}
