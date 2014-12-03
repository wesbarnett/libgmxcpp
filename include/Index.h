
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

/**
 * Contains all information from an index file. When constructed the index
 * file is read in. The names of each group are stored in headers. The locations
 * for each group are stored in the locations vector.
 */
class Index {
	private:
        vector <string> headers;
        vector < vector <int> > locations;
        int GetHeaderIndex(string groupName) const;
		bool isHeader(string line) const;
		bool IsIndexFile(string ndxfile) const;
		void PrintInfo() const;
	public:
		/**
		 * @brief Blank constructor used in Trajectory object 
		 * */
		Index();
		/**
		 * @brief Constructor which specifies index file.
		 * @details When constructed the index file is read into the
		 * corresponding data elements of the object and can be retrieved with
		 * getter functions below.
		 * @param ndxfile Name of index file to be read in.
		 * */
		Index(string ndxfile);
		/**
		 * @brief Reads in the GROMACS index file specified.
		 * @details See above constructor. This is used in the Trajectory object
		 * or when, in general, an Index object is created but no index file is
		 * specified initially.
		 */
		bool Set(string ndxfile);

		/**
		 * @brief Gets the size of an index group.
		 * @param groupName Name of group for which size is desired.
		 * @return Size of the group.
		 */
		int GetGroupSize(string groupName) const;

		/**
		 * @brief Gets the index location of the atom in the group specified.
		 * @details This returns in the index location of an atom relative to
		 * the entire system. That is, if you know a specific atom's location
		 * relative to an index group, i.e., it is the second atom in a group,
		 * then this gives the index number for it for the entire system, i.e.,
		 * the second atom in a group might be the 300th atom in the system.
		 * Look at how an index file is formatted to understand more thoroughly.
		 * @param groupName Name of group where at is located.
		 * @param atomNumber The location of the atom in the group.
		 */
        int GetLocation(string groupName, int atomNumber) const;
};

#endif
