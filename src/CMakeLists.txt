
add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp CommandLine.cpp
    Utils.cpp coordinates.cpp triclinicbox.cpp xdrfile.c xdrfile_xtc.c
    Clusters.cpp Uncertainty.cpp Topology.cpp)
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
