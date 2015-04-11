
add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp CommandLine.cpp
    Utils.cpp coordinates.cpp triclinicbox.cpp xdrfile.c xdrfile_xtc.c
    Clusters.cpp Uncertainty.cpp Topology.cpp)
set_target_properties(gmxcpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(gmxcpp PROPERTIES OUTPUT_NAME gmxcpp${BUILD_POSTFIX})

find_library(
    LIBGROMACS gromacs
    HINTS $ENV{GMXLDLIB}
)
if(${LIBGROMACS} STREQUAL "LIBGROMACS-NOTFOUND")
    message(FATAL_ERROR "Couldn't find the gromacs library")
endif()

message(STATUS "Found gromacs at: ${LIBGROMACS}")
target_link_libraries(gmxcpp ${LIBGROMACS})
target_include_directories(gmxcpp PUBLIC $ENV{GMXPREFIX}/include)

install (TARGETS gmxcpp LIBRARY DESTINATION lib)
