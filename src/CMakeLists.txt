
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

# -------------------------
# Find xdrfile
# -------------------------
find_package ( xdrfile REQUIRED )
message(STATUS "Found xdrfile library at: ${xdrfile_LIBRARIES}")
message(STATUS "Found xdrfile include dirs at: ${xdrfile_INCLUDE_DIRS}")

# -----------------------------------------------------------
# Additional files need to be compiled with avx support added
# -----------------------------------------------------------
if(${AVX})
    message(STATUS "Compiling with AVX support.")
    add_definitions(-DAVX)
    set(AVXFILECPP coordinates4.cpp coordinates8.cpp cubicbox8.cpp cubicbox_m256.cpp)
endif()

add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp Utils.cpp
coordinates.cpp cubicbox.cpp triclinicbox.cpp ${XDRFILEC} Clusters.cpp
Topology.cpp ${AVXFILECPP})

set_target_properties ( ${CMAKE_PROJECT_NAME}
  PROPERTIES
  OUTPUT_NAME ${CMAKE_PROJECT_NAME}
  PREFIX lib
  SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
  VERSION ${VERSION}
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" 
)

# -------------------------
# Find GROMACS
# -------------------------
find_library(
    LIBGROMACS gromacs
    HINTS $ENV{GMXLDLIB}
    HINTS ENV LD_LIBRARY_PATH
    REQUIRED
)

find_path(
    GROMACS_INCLUDES
    NAMES "gromacs/fileio/tpxio.h"
    HINTS "$ENV{GMXPREFIX}/include"
    HINTS ENV CPLUS_INCLUDE_PATH
    REQUIRED
)

message(STATUS "Found gromacs library at: ${LIBGROMACS}")
message(STATUS "Found gromacs headers at: ${GROMACS_INCLUDES}")

target_link_libraries(gmxcpp ${LIBGROMACS} ${XDRFILE_LIBRARIES})
target_include_directories(gmxcpp PUBLIC ${GROMACS_INCLUDES} ${XDRFILE_INCLUDE_DIRS})

install (TARGETS gmxcpp LIBRARY DESTINATION lib)
