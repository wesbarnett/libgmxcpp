
#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
using namespace std;

// Contains all information from an index file. When constructed the index
// file is read in. The names of each group are stored in headers. The locations
// for each group are stored in the locations vector.
class Index {
	private:
        vector <string> headers;
        vector < vector <int> > locations;
        int GetHeaderIndex(string header);
		bool isHeader(string line);
		bool IsIndexFile(string ndxfile);
		void PrintInfo();
	public:
		Index();
		Index(string ndxfile);
		bool Set(string filename);
		int GetGroupSize(string grpa);
        int GetLocation(string header, int i);
};
#endif
