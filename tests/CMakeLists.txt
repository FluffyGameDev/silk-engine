cmake_minimum_required (VERSION 3.15)

set(SILK_TESTS_SOURCE
    "source/unit_test_signal_slot.cpp"
)

add_executable(SilkTests ${SILK_TESTS_SOURCE})

set_property(TARGET SilkTests PROPERTY CXX_STANDARD 20)
set_property(TARGET SilkTests PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET SilkTests PROPERTY COMPILE_WARNING_AS_ERROR ON)

target_compile_options(SilkTests PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

find_package(googletest REQUIRED)

target_link_libraries(SilkTests PRIVATE silk::engine GTest::gtest_main)
