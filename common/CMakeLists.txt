
add_library (common timer.cpp)

add_custom_command(TARGET common PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/common/data $<TARGET_FILE_DIR:common>)