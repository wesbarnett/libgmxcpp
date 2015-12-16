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
set (gmxcpp_VERSION_MAJOR 1)
set (gmxcpp_VERSION_MINOR 0)
set(CMAKE_CXX_FLAGS "-std=gnu++11 -Wall -fopenmp")
add_subdirectory(include)
include_directories(include)
add_subdirectory(src)
add_subdirectory(docs)

project(tests)
add_subdirectory(tests)
enable_testing()
add_test(coordinates tests/coordinates_test)
add_test(triclinicbox tests/triclinicbox_test)
add_test(Utils tests/Utils_test)
add_test(Trajectory tests/Trajectory_test)
add_test(Clusters tests/Clusters_test)
add_test(Topology tests/Topology_test)
