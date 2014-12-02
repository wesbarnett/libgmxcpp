
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
        int GetHeaderIndex(string header) const;
		bool isHeader(string line) const;
		bool IsIndexFile(string ndxfile) const;
		void PrintInfo() const;
	public:
		Index();
		Index(string ndxfile);
		bool Set(string filename);
		int GetGroupSize(string grpa) const;
        int GetLocation(string header, int i) const;
};
#endif
