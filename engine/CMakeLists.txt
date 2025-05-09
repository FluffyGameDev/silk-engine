cmake_minimum_required (VERSION 3.8)

set(SILK_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
list(APPEND CMAKE_PREFIX_PATH "${SILK_ROOT_DIR}/cmake/modules")

include("${SILK_ROOT_DIR}/cmake/silk.cmake")

project("silk")

set(SILK_ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SILK_ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

setup_silk_source_groups(${CMAKE_CURRENT_SOURCE_DIR} ${SILK_ENGINE_INCLUDE_DIR} ${SILK_ENGINE_SOURCE_DIR})

file(GLOB_RECURSE SILK_ENGINE_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SILK_ENGINE_SOURCE_DIR}/*)
add_executable(SilkEngine ${SILK_ENGINE_SOURCE})

set_property(TARGET SilkEngine PROPERTY CXX_STANDARD 20)
set_property(TARGET SilkEngine PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(SilkEngine PRIVATE ${SILK_ENGINE_INCLUDE_DIR})

target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_LOGS)
target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_ASSERTS)
target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_PROFILER)


find_package(glad)
find_package(glfw)
target_link_libraries(SilkEngine PRIVATE glad glfw)
