#include <hdf5.h>
#include <string>
#include <iostream>
#include <numeric>
#include <vector>
#include "process_args.h"
#include "timer.h"

using std::string;
using std::vector;

const size_t MAXNAMELEN = 64;

int multiply(int x, int y) { return x * y; }

std::string read_string_data(hid_t file_id, const std::string &path) {
  hid_t dataset_id = H5Dopen(file_id, path.c_str(), H5P_DEFAULT);

  hid_t datatype = H5Dget_type(dataset_id); /* datatype handle */

  size_t size = H5Tget_size(datatype);

  char *data = new char[size];
  herr_t status =
      H5Dread(dataset_id, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
  H5Dclose(dataset_id);
  return std::string(data);
}

template <typename NumT>
std::vector<NumT> read_data(hid_t loc_id, const std::string &path,
                            const hid_t native_type) {
  hid_t dataset_id = H5Dopen(loc_id, path.c_str(), H5P_DEFAULT);
  hid_t dataspace = H5Dget_space(dataset_id); /* dataspace handle */
  int rank = H5Sget_simple_extent_ndims(dataspace);
  std::vector<hsize_t> dims_out(rank);
  int status_n = H5Sget_simple_extent_dims(dataspace, &dims_out[0], NULL);
  // std::cout << "rank=" << rank << " dims=" << dims_out[0] << std::endl;

  int product = std::accumulate(dims_out.begin(), dims_out.end(), 1, multiply);

  std::vector<NumT> data(product);
  herr_t status =
      H5Dread(dataset_id, native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data[0]);
  H5Dclose(dataset_id);
  return data;
}

herr_t file_info(hid_t loc_id, const char *name, const H5L_info_t *linfo,
                 void *opdata) {

  // find out if this is a group
  H5O_info_t object_info;
  H5Oget_info_by_name(loc_id, name, &object_info, H5P_DEFAULT);
  if ((object_info).type != H5O_TYPE_GROUP) {
    return 0;
  }

  string nameStr(name);
  if (nameStr.find("_events") != string::npos) {
    // std::cout << nameStr << std::endl;

    hid_t group = H5Gopen2(loc_id, name, H5P_DEFAULT);
    read_data<uint32_t>(group, "event_id", H5T_NATIVE_UINT);
    read_data<uint64_t>(group, "event_index", H5T_NATIVE_ULONG);
    read_data<float>(group, "event_time_offset", H5T_NATIVE_FLOAT);
    read_data<double>(group, "event_time_zero", H5T_NATIVE_DOUBLE);

    H5Gclose(group);
  }

  // open the group

  return 0;
}

void do_test_workspace2d(const std::string &filename) {
  common::Timer timer;

  /* Open an existing file. */
  hid_t file_id = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

  hid_t dataset_id1 = H5Gopen(file_id, "/mantid_workspace_1", H5P_DEFAULT);
  hid_t dataset_id2 =
      H5Gopen(file_id, "/mantid_workspace_1/workspace", H5P_DEFAULT);

  std::string path = "/mantid_workspace_1/instrument/instrument_xml/data";
  std::string instrumentXML = read_string_data(file_id, path);

  path = "/mantid_workspace_1/workspace/values";
  std::vector<double> values =
      read_data<double>(file_id, path, H5T_NATIVE_DOUBLE);

  path = "/mantid_workspace_1/workspace/errors";
  std::vector<double> errors =
      read_data<double>(file_id, path, H5T_NATIVE_DOUBLE);

  H5Gclose(dataset_id1);
  H5Gclose(dataset_id2);

  herr_t status = H5Fclose(file_id);

  timer.print_elapsed_ms();
}

void do_test_event_workspace(const std::string &filename) {
  common::Timer timer;

  /* Open an existing file. */
  hid_t file_id = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

  // hid_t entry_id1 = H5Gopen(file_id, "/entry", H5P_DEFAULT);      // SNS
  hid_t entry_id1 = H5Gopen(file_id, "/raw_data_1", H5P_DEFAULT); // ISIS

  // put together a list of NXevent_data
  H5Literate(entry_id1, H5_INDEX_NAME, H5_ITER_INC, NULL, file_info, NULL);

  H5Gclose(entry_id1);

  herr_t status = H5Fclose(file_id);

  timer.print_elapsed_ms();
}

int main(int argc, const char *argv[]) {
  // get the filename from the command line
  if (argc == 1) {
    common::print_usage(argv[0]);
    return 1;
  }

  // process every file
  int result = 0;
  for (int i = 1; i < argc; ++i) {
    const std::string filename = common::to_filename(argv[i]);
    if (filename.empty()) {
      std::cerr << "Failed to find readable file \"" << argv[i] << "\""
                << std::endl;
      result = -1;
    } else {
      // do_test_workspace2d(filename);
      do_test_event_workspace(filename);
    }
  }

  return result;
}
