cmake_minimum_required (VERSION 2.8.2)

set( THIRD_PARTY  $ENV{HOME}/  CACHE PATH "third party directory" )

set ( CMAKE_INCLUDE_PATH "${THIRD_PARTY}/include" )

set ( CMAKE_LIBRARY_PATH "${THIRD_PARTY}/lib/mac64" )

set ( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project (hdf5_compare)

find_package ( Nexus 4.3.0 REQUIRED )

find_package ( Poco REQUIRED )


SET (HDF5_DIR "${CMAKE_MODULE_PATH}" CACHE PATH "HDF5 Directory path")
find_package ( HDF5 COMPONENTS HL REQUIRED  CONFIGS hdf5-config.cmake )

add_subdirectory(with_hdf5)

add_subdirectory(with_nexus)

add_subdirectory(common)
