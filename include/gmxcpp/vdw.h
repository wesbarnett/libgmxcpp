
#ifndef VDW_H
#define VDW_H

#include <map>
#include <string>

std::map<std::string,double> VDW_RADII = {
    {"H", 0.12},
    {"C", 0.17},
    {"N", 0.155},
    {"O", 0.152}
};

std::map<std::string,double> VDW_RADII2 = {
    {"H", 0.0144},
    {"C", 0.0289},
    {"N", 0.024025},
    {"O", 0.023104}
};

#endif
