
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

find_library(
    LIBXDRFILE xdrfile
    HINTS ENV LD_LIBRARY_PATH
)

if(${LIBXDRFILE} STREQUAL "LIBXDRFILE-NOTFOUND")
   message(STATUS "Couldn't find the xdrfile library. Providing internally.")
   set(XDRFILEC xdrfile.c xdrfile_xtc.c)
else()
    message(STATUS "Found xdrfile library at: ${LIBXDRFILE}")
    find_path(
       XDRFILE_INCLUDES
       NAMES "xdrfile/xdrfile.h"
       NAMES "xdrfile/xdrfile_xtc.h"
       HINTS ENV CPLUS_INCLUDE_PATH
   )
   message(STATUS "Found xdrfile headers at: ${XDRFILE_INCLUDES}")
endif()

if(${AVX})
    message(STATUS "Compiling with AVX support.")
    add_definitions(-DAVX)
    set(AVXFILECPP coordinates4.cpp coordinates8.cpp cubicbox8.cpp cubicbox_m256.cpp)
endif()

add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp CommandLine.cpp
Utils.cpp coordinates.cpp cubicbox.cpp triclinicbox.cpp ${XDRFILEC}
Clusters.cpp Topology.cpp ${AVXFILECPP})
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
if(${LIBXDRFILE} STREQUAL "LIBXDRFILE-NOTFOUND")
    target_link_libraries(gmxcpp ${LIBGROMACS})
    target_include_directories(gmxcpp PUBLIC ${GROMACS_INCLUDES})
else()
    target_link_libraries(gmxcpp ${LIBGROMACS} ${LIBXDRFILE})
    target_include_directories(gmxcpp PUBLIC ${GROMACS_INCLUDES} ${XDRFILE_INCLUDES})
endif()

install (TARGETS gmxcpp LIBRARY DESTINATION lib)
