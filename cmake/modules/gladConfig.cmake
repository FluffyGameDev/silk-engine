
set(GLAD_DIR "${SILK_ROOT_DIR}/external/glad")
add_library(glad "${GLAD_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${GLAD_DIR}/include")
