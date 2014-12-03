
#include "Index.h"

Index::Index() {
	return;
}

Index::Index(string ndxfile) {
	Set(ndxfile);
	return;
}

// Reads in the index file, first getting the group names so that the locations
// vector can be properly sized. Then the index file is read again; if the line
// is a header, increment the group counter. Any other line is read in with a
// string stream into integers that are added to the vector located in this
// location in the locations vector.
bool Index::Set(string ndxfile) {

    ifstream iFS;
    istringstream linestream;
    string line, header;
    int num;
    int groupNum = 0;

	cout << "Reading in index file " << ndxfile << "...";

    if (!IsIndexFile(ndxfile)) throw runtime_error("Not a valid index file.");
    

    iFS.open(ndxfile.c_str());

	if (!iFS.is_open()) throw runtime_error("Cannot open index file.");

    while (getline(iFS,line)) {
        if (isHeader(line)) { 
            header = line.substr(2,line.length()-4);
            headers.push_back(header);
            groupNum++;
        }
    }
    locations.resize(groupNum);
    iFS.close();

    groupNum = -1;
    iFS.open(ndxfile.c_str());
    while (getline(iFS,line)) {
        if (isHeader(line)) { 
            groupNum++;
        } else if (line.length() != 0) {
            linestream.clear();
            linestream.str(line);
            while (linestream >> num) {
                locations.at(groupNum).push_back(num);
            }
        }
    }
    iFS.close();

    cout << "OK" << endl;

	cout << "Found the following groups: " << endl;
	PrintInfo();
	cout << "Finished reading in index file." << endl << endl;

    return true;

}

void Index::PrintInfo() const {
	for (int i=0; i<headers.size(); i++) {
		cout << "  " << headers.at(i);
		for (int j=0; j<10-headers.at(i).length(); j++) {
			cout << " ";
		}
		cout << "(" << locations.at(i).size() << " particles)" << endl;
	}
	return;

}

bool Index::IsIndexFile(string ndxfile) const {
    ifstream iFS;
    string line;

    iFS.open(ndxfile.c_str());
    getline(iFS,line);
    iFS.close();

    if (isHeader(line)) return true;

    return false;
}

// Translates the string name of a header to its correct index integer
// If the header is not present in the index file, throw an exception
int Index::GetHeaderIndex(string header) const {
    for (int i=0; i<headers.size(); i++) {
        if (headers.at(i) == header) return i;
    }
	throw runtime_error("Group " + header + " is not in the index file!");
}

int Index::GetGroupSize(string header) const {
    try {
	    return locations.at(GetHeaderIndex(header)).size();
	} catch(runtime_error &excpt) {
        terminate();
    }
}

// Gets the location of the ith atom in the header group specified
int Index::GetLocation(string header, int i) const {
    try {
        return locations.at(GetHeaderIndex(header)).at(i)-1;
	} catch(runtime_error &excpt) {
        terminate();
    }
}

bool Index::isHeader(string line) const {
    return (line[0] == '[' && line[line.length()-1] == ']');
}
