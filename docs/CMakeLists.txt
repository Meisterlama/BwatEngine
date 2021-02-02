file(GLOB_RECURSE DOC_BUILD
        build/*)

message(INFO ${DOC_BUILD})

add_custom_target( Documentation
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/BuildDoc.sh
        COMMENT DOC)

set(TRASH_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/build/
        ${CMAKE_CURRENT_SOURCE_DIR}/env/
        ${CMAKE_CURRENT_SOURCE_DIR}/xml/)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${TRASH_FILES}")
