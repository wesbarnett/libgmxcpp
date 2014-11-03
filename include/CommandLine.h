
#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <iostream>
#include <string>
using namespace std;

// Gets the value of an argument specified by the flag. So far this is only for
// a string. Returns false if the flag is not found or the argument is not
// specified.
bool getArgument(int argc, char* argv[], string flag, string *argToReturn);
bool checkHelpArg(int argc, char* argv[], string flag);

#endif
