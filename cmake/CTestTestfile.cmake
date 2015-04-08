# CMake generated Testfile for 
# Source directory: /home/wes/libgmxcpp
# Build directory: /home/wes/libgmxcpp/cmake
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(coordinates "tests/coordinates_test")
ADD_TEST(triclinicbox "tests/triclinicbox_test")
ADD_TEST(Utils "tests/Utils_test")
ADD_TEST(Trajectory "tests/Trajectory_test")
ADD_TEST(Clusters "tests/Trajectory_test")
SUBDIRS(include)
SUBDIRS(src)
SUBDIRS(docs)
SUBDIRS(tests)
