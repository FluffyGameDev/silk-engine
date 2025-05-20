cmake_minimum_required (VERSION 3.15)

file(GLOB_RECURSE SILK_RUNTIME_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} source/*)

add_library(SilkRuntime ${SILK_RUNTIME_SOURCE})
add_library(silk::runtime ALIAS SilkRuntime)

set_property(TARGET SilkRuntime PROPERTY CXX_STANDARD 20)
set_property(TARGET SilkRuntime PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET SilkRuntime PROPERTY COMPILE_WARNING_AS_ERROR ON)

target_include_directories(SilkRuntime PUBLIC include)

target_link_libraries(SilkRuntime PRIVATE silk::engine)
