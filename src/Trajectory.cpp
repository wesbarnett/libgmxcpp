
#include "Trajectory.h"

Trajectory::Trajectory() {}

// Initializes the trajectory object by finding out how many atoms are in the 
// system, saving how many frames we think there might be for memory allocation.
// TODO: put converstion of string to char array in its own function. Then calls
// read().
Trajectory::Trajectory(string filename, int initialFrames) {
	char cfilename[200];
	for (int i=0;i<filename.size();i++) {
		cfilename[i] = filename[i];
	}
	cfilename[filename.size()] = '\0';

	try {
		cout << "Opening xtc file " << filename << "...";
		if (read_xtc_natoms(cfilename,&natoms) != 0) throw runtime_error("Cannot open xtc file.");
	} catch(runtime_error &excpt) {
		cerr << endl << "Problem with creating Trajectory object." << endl;
		terminate();
	}
	cout << "OK" << endl;

	xd = xdrfile_open(cfilename,"r");
	this->initialFrames = initialFrames;
	nframes = 0;
	read();
	return;
}

Trajectory::Trajectory(string filename) {
	char cfilename[200];
	for (int i=0;i<filename.size();i++) {
		cfilename[i] = filename[i];
	}
	cfilename[filename.size()] = '\0';

	try {
		cout << "Opening xtc file " << filename << "...";
		if (read_xtc_natoms(cfilename,&natoms) != 0) throw runtime_error("Cannot open xtc file.");
	} catch(runtime_error &excpt) {
		cerr << endl << "Problem with creating Trajectory object." << endl;
		terminate();
	}
	cout << "OK" << endl;

	xd = xdrfile_open(cfilename,"r");
	initialFrames = 100000;
	nframes = 0;
	read();
	return;
}

Trajectory::Trajectory(string filename, string ndxfile) {
	char cfilename[200];
	for (int i=0;i<filename.size();i++) {
		cfilename[i] = filename[i];
	}
	cfilename[filename.size()] = '\0';

	try {
		index.Set(ndxfile);
		cout << "Opening xtc file " << filename << "...";
		if (read_xtc_natoms(cfilename,&natoms) != 0) throw runtime_error("Cannot open xtc file.");
	} catch(runtime_error &excpt) {
		cerr << endl << "Problem with creating Trajectory object." << endl;
		terminate();
	}
	cout << "OK." << endl;

	xd = xdrfile_open(cfilename,"r");
	initialFrames = 100000;
	nframes = 0;
	read();
	return;
}

// Reads in all of the frames from the xtc file. First, we allocate memory 
// for our temporary Frame array. Then we allocate memory for the vectors 
// for this frame based on the number of atoms read in from earlier. We 
// cycle through each frame, saving the important info for each step into 
// the temporary frame array. After this we allocate memory for the final 
// frame array based on how many frames were read in. Lastly, we delete the 
// temporary array.
void Trajectory::read() {
	int status = 0;
	int step;
	matrix box;
	float time;
	rvec *x;
	int j = 0;
	Frame *tmpArray;
	tmpArray = new Frame[initialFrames];

	cout << natoms << " particles are in the system." << endl;

	cout << "Allocated memory for " << initialFrames << " frames of data." << endl;
	while (status == 0) {
		if (nframes % 10 == 0) cout << "Reading frame: " << nframes << "\r";
		x = new rvec[natoms];
		status = read_xtc(xd,natoms,&step,&time,box,x,&prec);
		if (status !=0) break;
		tmpArray[nframes].Set(step,time,box,x);
		nframes++;
    }

	cout << endl << "Read in " << nframes << " frames." << endl;
	cout << "Freeing up memory..." << endl;
	frameArray = new Frame[nframes];
	for (j=0; j<nframes; j++) {
		frameArray[j] = tmpArray[j];
	}
	delete tmpArray;

	status = xdrfile_close(xd);
	cout << "Finished reading in xtc file." << endl;
	return;
}

// Gets the xyz coordinates when the frame and atom number are specified.
void Trajectory::GetXYZ(int frame, int atom, rvec xyz) {
    xyz[X] = frameArray[frame].x[atom][X];
    xyz[Y] = frameArray[frame].x[atom][Y];
    xyz[Z] = frameArray[frame].x[atom][Z];
    return;
}

// Gets the xyz coordinates when the frame, group, and atom number are
// specified.
void Trajectory::GetXYZ(int frame, string group, int atom, rvec xyz) {
	int location = index.GetLocation(group, atom);
	if (location == -1) return;
    xyz[X] = frameArray[frame].x[location][X];
    xyz[Y] = frameArray[frame].x[location][Y];
    xyz[Z] = frameArray[frame].x[location][Z];
    return;
}

void Trajectory::GetXYZ(string group, int frame, int atom, rvec xyz) {
    this->GetXYZ(frame,group,atom,xyz);
    return;
}

// Gets the box dimensions for a specific frame
void Trajectory::GetBox(int frame, matrix box) {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			box[i][j] = frameArray[frame].box[i][j];
		}
	}
	return;
}

int Trajectory::GetNAtoms(string group) {
	return index.GetGroupSize(group);
}

int Trajectory::GetNAtoms() {
    return natoms;
}

int Trajectory::GetNFrames() {
	return nframes;
}
float Trajectory::GetTime(int frame) {
	return frameArray[frame].GetTime();
}

int Trajectory::GetStep(int frame) {
	return frameArray[frame].GetStep();
}
