cmake_minimum_required (VERSION 3.8)

project ("silk")


function(setup_source_groups root_dir include_dir source_dir)

    file(GLOB header_files RELATIVE ${root_dir} ${include_dir}/*)
    file(GLOB source_files RELATIVE ${root_dir} ${source_dir}/*)

    foreach(file_path ${header_files})
        if(IS_DIRECTORY ${root_dir}/${file_path})
            get_filename_component(file_name ${file_path} NAME)
            setup_source_groups(${root_dir} ${include_dir}/${file_name} ${source_dir}/${file_name})
        else()
            list(APPEND current_group_files ${file_path})
        endif()
    endforeach()

    foreach(file_path ${source_files})
        if(NOT IS_DIRECTORY ${root_dir}/${file_path})
            list(APPEND current_group_files ${file_path})
        endif()
    endforeach()

    file(RELATIVE_PATH group_name ${root_dir} ${source_dir})
    source_group(${group_name} FILES ${current_group_files})

endfunction()


set(SILK_ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SILK_ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

setup_source_groups(${CMAKE_CURRENT_SOURCE_DIR} ${SILK_ENGINE_INCLUDE_DIR} ${SILK_ENGINE_SOURCE_DIR})

file(GLOB_RECURSE SILK_ENGINE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SILK_ENGINE_INCLUDE_DIR}/*)
file(GLOB_RECURSE SILK_ENGINE_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SILK_ENGINE_SOURCE_DIR}/*)

add_executable(SilkEngine ${SILK_ENGINE_HEADERS} ${SILK_ENGINE_SOURCE})

target_include_directories(SilkEngine PRIVATE ${SILK_ENGINE_INCLUDE_DIR})

set_property(TARGET SilkEngine PROPERTY CXX_STANDARD 17)

target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_LOGS)
target_compile_definitions(SilkEngine PUBLIC SILK_ENABLE_ASSERTS)
