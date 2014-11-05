cmake_minimum_required (VERSION 2.8.2)

set( THIRD_PARTY  $ENV{HOME}/  CACHE PATH "third party directory" )

set ( CMAKE_INCLUDE_PATH "${THIRD_PARTY}/include" )

set ( CMAKE_LIBRARY_PATH "${THIRD_PARTY}/lib/mac64" ) # TODO fix for other OS

set ( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project (hdf5_compare)

find_package ( Nexus 4.3.0 REQUIRED )

find_package ( Poco REQUIRED )

SET (HDF5_DIR "${CMAKE_MODULE_PATH}" CACHE PATH "HDF5 Directory path")
find_package ( HDF5 COMPONENTS HL REQUIRED  CONFIGS hdf5-config.cmake )

add_library (common process_args.cpp timer.cpp)

add_custom_command(TARGET common PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:common>)

include_directories ( ${NEXUS_INCLUDE_DIR} ${HDF5_INCLUDE_DIRS} ${THIRD_PARTY}/include ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(with_hdf5 with_hdf5.cpp)
target_link_libraries (with_hdf5 common ${HDF5_LIBRARIES}  ${POCO_LIB_FOUNDATION})

add_executable (with_nexus with_nexus.cpp)
target_link_libraries ( with_nexus common ${NEXUS_C_LIBRARIES} ${POCO_LIB_FOUNDATION})
