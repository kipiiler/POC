find_package(Doxygen)

if (DOXYGEN_FOUND)
    message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE} -- ${DOXYGEN_VERSION}")

    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/)
    set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
    set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
                        MAIN_DEPENDENCY ${DOXYFILE}
                        COMMENT "Generate Doxygen documentation"
                        VERBATIM
    )

    add_custom_target(GenDocs ALL DEPENDS ${DOXYGEN_INDEX_FILE})
endif()
