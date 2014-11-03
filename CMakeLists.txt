cmake_minimum_required (VERSION 2.8.2)

set( THIRD_PARTY "unknown" CACHE STRING "third party directory" )

set ( CMAKE_INCLUDE_PATH "${THIRD_PARTY}/include" )

set ( CMAKE_LIBRARY_PATH "${THIRD_PARTY}/lib/mac64" )

message(status ${CMAKE_LIBRARY_PATH})
message(status ${CMAKE_INCLUDE_PATH})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

project (hdf5_compare)

find_package ( Nexus 4.3.0 REQUIRED )

add_subdirectory(with_hdf5)

add_subdirectory(with_nexus)

add_subdirectory(common)
