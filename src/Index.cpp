
#include "Index.h"
#include <iostream>
#include <iomanip>
using namespace std;


Index::Index() {
	return;
}

Index::Index(string ndxfile) {
	Set(ndxfile);
	return;
}

// TODO: figure out how to use maps
// Reads in the index file, first getting the headers. Then reads in the index
// file a second time, storing the locations in a two dimensional array.
void Index::Set(string ndxfile) {

	cout << "Reading in " << ndxfile << "." << endl;
    ifstream iFS;
    string line, header;
    int a, num;
    int groupNum = 0;

    iFS.open(ndxfile.c_str());

	if (!iFS.is_open()) {
		cout << "ERROR: Cannot open " << ndxfile << "." << endl;
		return;
	}
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
            for (int i=0; i<line.length(); i++) {
				if (i == 0) {
					a = i;
				} else {
					if (line.at(i-1) == ' ' && line.at(i) != ' ') {
						a = i;
					} else if (line.at(i-1) != ' ' && line.at(i) == ' ') {
                        num = atoi(line.substr(a,i).c_str());
                        locations.at(groupNum).push_back(num);
					}
				}
            }
        }
    }
    iFS.close();

	cout << "Found the following groups: " << endl;
	PrintInfo();
	cout << "Finished reading in index file." << endl;

    return;

}

void Index::PrintInfo() {
	for (int i=0; i<headers.size(); i++) {
		cout << "  " << headers.at(i);
		for (int j=0; j<10-headers.at(i).length(); j++) {
			cout << " ";
		}
		cout << "(" << locations.at(i).size() << " particles)" << endl;
	}
	return;

}

// Translates the string name of a header to its correct index integer
int Index::GetHeaderIndex(string header) {
    for (int i=0; i<headers.size(); i++) {
        if (headers.at(i) == header) {
            return i;
        }
    }
	cout << "ERROR: Group '" << header << "' not found in index file." << endl;
    return -1;
}

int Index::GetGroupSize(string header) {
    int locationIndex = GetHeaderIndex(header);
	if (locationIndex == -1) return -1;
	return locations.at(locationIndex).size();
}

// Gets the location of the ith atom in the header group specified
int Index::GetLocation(string header, int i) {
    int locationIndex = GetHeaderIndex(header);
	if (locationIndex == -1) return -1;
    return locations.at(locationIndex).at(i)-1;
}

bool Index::isHeader(string line) {
    return (line[0] == '[' && line[line.length()-1] == ']');
}
