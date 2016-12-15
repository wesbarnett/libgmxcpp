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

cmake_minimum_required(VERSION 2.8)
project(gmxcpp)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# -------------------------
# Package version
# -------------------------
file ( STRINGS "${CMAKE_SOURCE_DIR}/.VERSION" VERSION )
string( REPLACE "." ";" VERSION_LIST ${VERSION} )
list(GET VERSION_LIST 0 VERSION_MAJOR)
list(GET VERSION_LIST 1 VERSION_MINOR)
list(GET VERSION_LIST 2 VERSION_PATCH)
set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message ( STATUS "CMake build configuration for ${CMAKE_PROJECT_NAME} ${PROJECT_VERSION}" )
string ( TOLOWER ${CMAKE_PROJECT_NAME} PACKAGE_NAME )
set ( PACKAGE_VERSION "${PACKAGE_NAME}-${VERSION}" )

# --------------------------
# Optional banner
# --------------------------
set(BANNER ON CACHE INTERNAL "")
if(${BANNER})
    add_definitions(-DBANNER)
else()
    message(STATUS "Compiling without banner.")
endif()

# ----------------------------------
# Add AVX instructions if requested
# ---------------------------------
set(AVX OFF CACHE INTERNAL "")
if(${AVX})
    set(CMAKE_CXX_FLAGS "-O3 -Wall -march=native")
else()
    set(CMAKE_CXX_FLAGS "-O3 -Wall")
endif()

add_subdirectory(include)
include_directories(include)
add_subdirectory(src)
add_subdirectory(docs)

# ----------------------------------
# Tests
# ---------------------------------
add_subdirectory(tests)
enable_testing()
add_test(coordinates tests/coordinates_test)
add_test(triclinicbox tests/triclinicbox_test)
add_test(Utils tests/Utils_test)
add_test(Trajectory tests/Trajectory_test)
add_test(Clusters tests/Clusters_test)
add_test(Topology tests/Topology_test)
