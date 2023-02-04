function(target_add_asset TARGET FOLDER ASSET_PATH)

    get_filename_component(ASSET_NAME ${ASSET_PATH} NAME)

    if(CMAKE_GENERATOR STREQUAL Xcode)
        set(ASSET_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${TARGET}/$<CONFIG>/${FOLDER}/${ASSET_NAME}")
    else()
        set(ASSET_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${TARGET}/${FOLDER}/${ASSET_NAME})
    endif()

    get_filename_component(ASSET_OUTPUT_DIR ${ASSET_OUTPUT_PATH} DIRECTORY)

    add_custom_command(
        COMMENT "Copying asset: ${FOLDER}/${ASSET_NAME}"
        # TARGET ${TARGET} POST_BUILD
        OUTPUT ${ASSET_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSET_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${ASSET_PATH} ${ASSET_OUTPUT_PATH}
        MAIN_DEPENDENCY ${ASSET_PATH}
        VERBATIM
    )

source_group("${FOLDER}" FILES ${ASSET_PATH})
    target_sources(${TARGET} PRIVATE ${ASSET_PATH})

endfunction(target_add_asset)

function(target_add_assets TARGET FOLDER)
    foreach(ASSET IN LISTS ARGN)
        target_add_asset(${TARGET} ${FOLDER} ${ASSET})
    endforeach()
endfunction(target_add_assets)
