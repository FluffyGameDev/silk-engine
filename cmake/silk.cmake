
function(setup_silk_source_groups root_dir include_dir source_dir)

    file(GLOB header_files RELATIVE ${root_dir} ${include_dir}/*)
    file(GLOB source_files RELATIVE ${root_dir} ${source_dir}/*)

    foreach(file_path ${header_files})
        if(IS_DIRECTORY ${root_dir}/${file_path})
            get_filename_component(file_name ${file_path} NAME)
            setup_silk_source_groups(${root_dir} ${include_dir}/${file_name} ${source_dir}/${file_name})
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
