cmake_minimum_required (VERSION 3.15)

set(SILK_SANDBOX_SOURCE
    "source/silk_sandbox.cpp"
)

add_executable(SilkSandbox ${SILK_SANDBOX_SOURCE})

target_link_libraries(SilkSandbox PRIVATE silk::engine)
