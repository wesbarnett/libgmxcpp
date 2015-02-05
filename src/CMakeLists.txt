
add_library(gmxcpp SHARED Frame.cpp Index.cpp Trajectory.cpp CommandLine.cpp
    Utils.cpp coordinates.cpp triclinicbox.cpp)
set_target_properties(gmxcpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(gmxcpp PROPERTIES OUTPUT_NAME gmxcpp${BUILD_POSTFIX})
target_link_libraries(gmxcpp xdrfile)
install (TARGETS gmxcpp LIBRARY DESTINATION lib)
