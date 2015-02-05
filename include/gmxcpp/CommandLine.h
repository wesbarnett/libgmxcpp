
/** @file
 * @author James W. Barnett jbarnet4@tulane.edu
 * @date December 5, 2014
 *  @brief A couple of command line utilities.
 */

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <iostream>
#include <string>
using namespace std;


/**
 * @brief Parse the command line
 * @details Gets the value of an argument specified by the flag. So far this is only for
 * a string. Returns false if the flag is not found or the argument is not
 * specified.
 * @param argc Number of command line arguments.
 * @param argv[] Array of command line arguments.
 * @param flag The flag to search for in the arguments, i.e., "-f" or something
 * similar.
 * @param argToReturn If the flag is found, return the corresponding argument to
 * this variable, i.e., "-f traj.xtc" would return "traj.xtc" if the "-f" flag
 * is passed."
 * @return Whether or not the flag was found and had a valid argument.
 * @todo Handle other argument types.
 */

bool getArgument(int argc, char* argv[], string flag, string *argToReturn);
/**
 * @brief Check if help command flag was specified.
 * @details Runs through the command line arguments to see if a specific flag
 * was found. If so, returns true so that the programmer can do something.
 * Usually the help flag is specified as "-h".
 * @return Whether or not the help flag was specified.
 * @param argc Number of command line arguments.
 * @param argv[] Array of command line arguments.
 * @param flag The flag to check for. Normally this could be "-h".
 */
bool checkHelpArg(int argc, char* argv[], string flag);

#endif
