include_directories ( ${NEXUS_INCLUDE_DIR} ${THIRD_PARTY}/include ${CMAKE_CURRENT_SOURCE_DIR}/../common )

add_executable (with_nexus trial.cpp)

target_link_libraries ( with_nexus common ${NEXUS_C_LIBRARIES} ${POCO_LIB_FOUNDATION})