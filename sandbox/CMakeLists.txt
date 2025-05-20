cmake_minimum_required (VERSION 3.15)

set(SILK_SANDBOX_SOURCE
    "source/silk_sandbox.cpp"
)

add_executable(SilkSandbox ${SILK_SANDBOX_SOURCE})

set_property(TARGET SilkSandbox PROPERTY CXX_STANDARD 20)
set_property(TARGET SilkSandbox PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET SilkSandbox PROPERTY COMPILE_WARNING_AS_ERROR ON)

target_link_libraries(SilkSandbox PRIVATE silk::engine silk::runtime)
