#include <hdf5.h>
#include <string>
#include <iostream>
#include <numeric>
#include "timer.h"
#include "Poco/Path.h"
#include "Timer.h"

int multiply(int x, int y)
{
  return x * y;
}

std::vector<double> read_double_data(hid_t file_id, const std::string& path)
{
  hid_t dataset_id = H5Dopen(file_id, path.c_str(), H5P_DEFAULT);
  hid_t dataspace = H5Dget_space(dataset_id); /* dataspace handle */
  int rank = H5Sget_simple_extent_ndims(dataspace);
  std::vector<hsize_t> dims_out(rank);
  int status_n = H5Sget_simple_extent_dims(dataspace, &dims_out[0], NULL);

  int product = std::accumulate(dims_out.begin(), dims_out.end(), 1, multiply);

  std::vector<double> data(product);
  herr_t status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data[0]);
  H5Dclose(dataset_id);
  return data;
}

int main()
{
  common::Timer timer;
  timer.start();

  Poco::Path file_path("../common/INTER00013460.nxs");
  const std::string file = file_path.toString();

  /* Open an existing file. */
  hid_t file_id = H5Fopen(file.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

  hid_t dataset_id1 = H5Gopen(file_id, "/mantid_workspace_1", H5P_DEFAULT);
  hid_t dataset_id2 = H5Gopen(file_id, "/mantid_workspace_1/workspace", H5P_DEFAULT);

  std::string path = "/mantid_workspace_1/workspace/values";
  std::vector<double> values = read_double_data(file_id, path);

  path = "/mantid_workspace_1/workspace/errors";
  std::vector<double> errors = read_double_data(file_id, path);

  H5Gclose(dataset_id1);
  H5Gclose(dataset_id2);

  herr_t status = H5Fclose(file_id);

  timer.stop();

  std::cout << "Elapsed time in ms: " << timer.elapsed_ms() << std::endl;

  return 0;
}
