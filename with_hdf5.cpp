#include <hdf5.h>
#include <string>
#include <iostream>
#include <numeric>
#include "process_args.h"
#include "timer.h"
#include "Poco/Path.h"

int multiply(int x, int y)
{
  return x * y;
}

std::string read_string_data(hid_t file_id, const std::string& path)
{
  hid_t dataset_id = H5Dopen(file_id, path.c_str(), H5P_DEFAULT);

  hid_t datatype = H5Dget_type(dataset_id); /* datatype handle */

  size_t size = H5Tget_size(datatype);

  char* data = new char[size];
  herr_t status = H5Dread(dataset_id, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
  H5Dclose(dataset_id);
  return std::string(data);
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

void do_test_workspace2d(const std::string& filename)
{
  common::Timer timer;
  timer.start();

  /* Open an existing file. */
  hid_t file_id = H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

  hid_t dataset_id1 = H5Gopen(file_id, "/mantid_workspace_1", H5P_DEFAULT);
  hid_t dataset_id2 = H5Gopen(file_id, "/mantid_workspace_1/workspace", H5P_DEFAULT);

  std::string path = "/mantid_workspace_1/instrument/instrument_xml/data";
  std::string instrumentXML = read_string_data(file_id, path);

  path = "/mantid_workspace_1/workspace/values";
  std::vector<double> values = read_double_data(file_id, path);

  path = "/mantid_workspace_1/workspace/errors";
  std::vector<double> errors = read_double_data(file_id, path);

  H5Gclose(dataset_id1);
  H5Gclose(dataset_id2);

  herr_t status = H5Fclose(file_id);

  timer.stop();

  std::cout << timer.elapsed_ms() << std::endl;
}

void do_test_event_workspace(const std::string& relative_file_path)
{
  //TODO. The HDF5/Nexus file structure is different from the workspace2D so new implementation needed of above.
}

int main(int argc, const char* argv[])
{
  // get the filename from the command line
  if (argc == 1)
  {
   common::print_usage(argv[0]);
    return 1;
  }

  // process every file
  int result = 0;
  for (int i = 1; i < argc; ++i)
  {
    const std::string filename = common::to_filename(argv[i]);
    if (filename.empty())
    {
      std::cerr << "Failed to find readable file \"" << argv[i] << "\"" << std::endl;
      result = -1;
    }
    else
    {
      do_test_workspace2d(filename);
    }
  }

  return result;
}
