function(source_group_by_folder)
    cmake_parse_arguments(
        PARSED_ARGS
        "" # Options
        "" # 1 value args
        "HEADERS;SOURCES" # multi value args
        ${ARGN}
    )
    
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
        source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" 
            PREFIX "Source Files"
            FILES ${PARSED_ARGS_SOURCES}
        )
        source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" 
            PREFIX "Header Files"
            FILES ${PARSED_ARGS_HEADERS}
        )
    else()
        source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${PARSED_ARGS_HEADERS} ${PARSED_ARGS_SOURCES})
    endif()
endfunction()