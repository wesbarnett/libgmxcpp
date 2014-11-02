
#ifndef UTILS_H
#define UTILS_H

#include "xdrfile.h"
#include "xdrfile_xtc.h"
#include <math.h>
#include <cmath>

const int X = 0;
const int Y = 1;
const int Z = 2;

void pbc(rvec a, matrix box);
void cross(rvec a, rvec b, rvec r);

#endif
