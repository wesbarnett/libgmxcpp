find_package(Sphinx)

if(NOT DEFINED SPHINX_THEME)
    set(SPHINX_THEME default)
endif()

if(NOT DEFINED SPHINX_THEME_DIR)
    set(SPHINX_THEME_DIR)
endif()

# HTML output directory
set(SPHINX_MAN_DIR "${CMAKE_CURRENT_BINARY_DIR}/html")

add_custom_target(docs COMMAND
    ${SPHINX_EXECUTABLE}
        -b html
        -c ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${SPHINX_MAN_DIR}"
    COMMENT "Building HTML documentation with Sphinx.")
