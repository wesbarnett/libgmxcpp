
add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp CommandLine.cpp
    Utils.cpp coordinates.cpp triclinicbox.cpp xdrfile.c xdrfile_xtc.c
    Clusters.cpp Topology.cpp)
set_target_properties(gmxcpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(gmxcpp PROPERTIES OUTPUT_NAME gmxcpp${BUILD_POSTFIX})

find_library(
    LIBGROMACS gromacs
    HINTS $ENV{GMXLDLIB}
    HINTS ENV LD_LIBRARY_PATH
    HINTS ENV LIBRARY_PATH
    HINTS "/usr/local/gromacs/lib"
    HINTS "/usr/local/gromacs/lib64"
)

if(${LIBGROMACS} STREQUAL "LIBGROMACS-NOTFOUND")
    message(FATAL_ERROR "Couldn't find the gromacs library. Try sourcing GMXRC 
    or set the LIBRARY_PATH environmental variable to the GROMACS library
    directory.")
endif()
message(STATUS "Found gromacs library at: ${LIBGROMACS}")

find_path(
    GROMACS_INCLUDES
    NAMES "gromacs/fileio/tpxio.h"
    HINTS "$ENV{GMXPREFIX}/include"
    HINTS ENV CPLUS_INCLUDE_PATH
    HINTS ENV LD_INCLUDE_PATH
    HINTS ENV INCLUDE_PATH
    HINTS "/usr/local/gromacs/include"
)

if(${GROMACS_INCLUDES} STREQUAL "GROMACS_INCLUDES-NOTFOUND")
    message(FATAL_ERROR "Couldn't find the gromacs header files. Try sourcing
    GMXRC or set the CPLUS_INCLUDE_PATH environmental variable to the GROMACS
    include directory.")
endif()
message(STATUS "Found gromacs headers at: ${GROMACS_INCLUDES}")

target_link_libraries(gmxcpp ${LIBGROMACS})
target_include_directories(gmxcpp PUBLIC ${GROMACS_INCLUDES})

install (TARGETS gmxcpp LIBRARY DESTINATION lib)
