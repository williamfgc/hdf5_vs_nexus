
add_executable(with_hdf5 trial.cpp)

include_directories (${HDF5_INCLUDE_DIRS})

target_link_libraries (with_hdf5 ${HDF5_LIBRARIES})
