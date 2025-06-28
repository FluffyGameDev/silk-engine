cmake_minimum_required (VERSION 3.15)

set(SILK_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
list(APPEND CMAKE_PREFIX_PATH "${SILK_ROOT_DIR}/cmake/modules")

project("silk")

add_subdirectory(engine)
add_subdirectory(modules/runtime)
add_subdirectory(sandbox)
add_subdirectory(tests)
