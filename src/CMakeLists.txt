
# libgmxcpp 
#
# Copyright (C) 2015 James W. Barnett <jbarnet4@tulane.edu>
#  
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
 
# This program is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 51
# Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
# The full license is located in a text file titled "LICENSE" in the root
# directory of the source.

add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp CommandLine.cpp
    Utils.cpp coordinates.cpp coordinates4.cpp coordinates8.cpp cubicbox.cpp
    cubicbox_m256.cpp triclinicbox.cpp xdrfile.c xdrfile_xtc.c Clusters.cpp
    Topology.cpp)
set_target_properties(gmxcpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(gmxcpp PROPERTIES OUTPUT_NAME gmxcpp${BUILD_POSTFIX})

find_library(
    LIBGROMACS gromacs
    HINTS $ENV{GMXLDLIB}
    HINTS ENV LD_LIBRARY_PATH
)

if(${LIBGROMACS} STREQUAL "LIBGROMACS-NOTFOUND")
    message(FATAL_ERROR "Couldn't find the gromacs library.")
endif()

find_path(
    GROMACS_INCLUDES
    NAMES "gromacs/fileio/tpxio.h"
    HINTS "$ENV{GMXPREFIX}/include"
    HINTS ENV CPLUS_INCLUDE_PATH
)

if(${GROMACS_INCLUDES} STREQUAL "GROMACS_INCLUDES-NOTFOUND")
    message(FATAL_ERROR "Couldn't find the gromacs header files.")
endif()

message(STATUS "Found gromacs library at: ${LIBGROMACS}")
message(STATUS "Found gromacs headers at: ${GROMACS_INCLUDES}")
target_link_libraries(gmxcpp ${LIBGROMACS})
target_include_directories(gmxcpp PUBLIC ${GROMACS_INCLUDES})

install (TARGETS gmxcpp LIBRARY DESTINATION lib)
