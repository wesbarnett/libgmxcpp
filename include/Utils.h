
#ifndef UTILS_H
#define UTILS_H

#include "xdrfile/xdrfile.h"
#include "xdrfile/xdrfile_xtc.h"
#include <math.h>
#include <cmath>
#include <sys/stat.h>
#include <string>
#include <fstream>
using namespace std;

const int X = 0;
const int Y = 1;
const int Z = 2;

// Prints out coordinates cleanly
ostream& operator<<(ostream &os, rvec xyz);
ostream& operator<<(ostream &os, matrix box);

void pbc(rvec a, matrix box);
void cross(rvec a, rvec b, rvec r);
double distance(rvec a, rvec b, matrix box);
double distance2(rvec a, rvec b, matrix box);
double magnitude(rvec x);
double volume(matrix box);
bool fileExists(string filename);

#endif
