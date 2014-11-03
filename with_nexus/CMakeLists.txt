
include_directories ( SYSTEM ${NEXUS_INCLUDE_DIR} )

add_executable (with_nexus trial.cpp)

target_link_libraries ( with_nexus ${NEXUS_C_LIBRARIES} )