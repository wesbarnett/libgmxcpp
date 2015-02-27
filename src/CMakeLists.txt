
add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp CommandLine.cpp
    Utils.cpp coordinates.cpp triclinicbox.cpp xdrfile.c xdrfile_xtc.c
    Clusters.cpp Uncertainty.cpp)
set_target_properties(gmxcpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(gmxcpp PROPERTIES OUTPUT_NAME gmxcpp${BUILD_POSTFIX})
install (TARGETS gmxcpp LIBRARY DESTINATION lib)
