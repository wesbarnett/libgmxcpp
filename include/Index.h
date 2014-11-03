
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
        vector < vector <int> > locations;
        vector <string> headers;
		bool isHeader(string line);
        int GetHeaderIndex(string header);
		void PrintInfo();
		bool IsIndexFile(string ndxfile);
	public:
		Index(string ndxfile);
		Index();
		int GetGroupSize(string grpa);
        int GetLocation(string header, int i);
		bool Set(string filename);
};
#endif
