cmake_minimum_required (VERSION 3.15)


include("${SILK_ROOT_DIR}/cmake/silk.cmake")

set(SILK_ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SILK_ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

setup_silk_source_groups(${CMAKE_CURRENT_SOURCE_DIR} ${SILK_ENGINE_INCLUDE_DIR} ${SILK_ENGINE_SOURCE_DIR})

file(GLOB_RECURSE SILK_ENGINE_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SILK_ENGINE_SOURCE_DIR}/*)
add_library(SilkEngine ${SILK_ENGINE_SOURCE})

set_property(TARGET SilkEngine PROPERTY CXX_STANDARD 20)
set_property(TARGET SilkEngine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET SilkEngine PROPERTY COMPILE_WARNING_AS_ERROR ON)

target_compile_options(SilkEngine PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_include_directories(SilkEngine PUBLIC ${SILK_ENGINE_INCLUDE_DIR})

target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_LOGS)
target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_ASSERTS)
target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_PROFILER)
target_compile_definitions(SilkEngine PUBLIC SILK_GRAPHICS_DEBUGGING)


find_package(glad)
find_package(glfw)
find_package(imgui)
find_package(nlohmann_json)
target_link_libraries(SilkEngine PRIVATE glad glfw nlohmann_json)
target_link_libraries(SilkEngine PUBLIC imgui)

add_library(silk::engine ALIAS SilkEngine)
