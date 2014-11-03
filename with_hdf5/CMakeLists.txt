

include_directories ( ${HDF5_INCLUDE_DIRS} ${THIRD_PARTY}/include ${CMAKE_CURRENT_SOURCE_DIR}/../common)

add_executable(with_hdf5 trial.cpp)

target_link_libraries (with_hdf5 common ${HDF5_LIBRARIES}  ${POCO_LIB_FOUNDATION})
