#include <nexus/napi.h>
#include <nexus/NeXusFile.hpp>
#include <nexus/NeXusException.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "process_args.h"
#include "timer.h"

using common::Timer;

std::string read_string_data(NXhandle &fileId, const std::string &path) {
  int rank;
  int dims[4];
  int type;
  NXopendata(fileId, path.c_str());
  NXgetinfo(fileId, &rank, dims, &type);
  int n = dims[0];
  char *buffer = new char[n];
  NXstatus stat = NXgetdata(fileId, buffer);
  NXclosedata(fileId);
  return std::string(buffer);
}

std::vector<double> read_double_data(NXhandle &fileId,
                                     const std::string &path) {
  NXopendata(fileId, path.c_str());
  int rank;
  int dims[4];
  int type;
  NXgetinfo(fileId, &rank, dims, &type);
  int n = dims[0] * dims[1];
  std::vector<double> vec(n);
  NXstatus stat = NXgetdata(fileId, &vec[0]);
  NXclosedata(fileId);
  return vec;
}

void do_test_workspace2d(const std::string &filename) {
  Timer timer;
  timer.reset();

  NXhandle fileId;
  NXstatus stat = NXopen(filename.c_str(), NXACC_READ, &fileId);

  // Open the workspace group
  std::string path = "mantid_workspace_1";
  NXopengroup(fileId, path.c_str(), "NXentry");

  path = "instrument/instrument_xml/data";
  read_string_data(fileId, path);

  // Open the workspace entry
  path = "workspace";
  NXopengroup(fileId, path.c_str(), "NXdata");

  // Open values
  path = "values";
  read_double_data(fileId, path);

  // Open errors
  path = "errors";
  read_double_data(fileId, path);

  // Close the groups
  NXclosegroup(fileId);
  NXclosegroup(fileId);

  // Close the file
  NXclose(&fileId);

  timer.print_elapsed_ms();
};

void do_test_event_workspace(const std::string &filename) {
  Timer timer;

  NeXus::File file(filename);
  // NXhandle fileId;
  // NXstatus stat = NXopen(filename.c_str(), NXACC_READ, &fileId);
  // NXopengroup(fileId, "entry", "NXentry");

  // // get a list of all NXevent_data
  // std::std::vector<std::string> eventDataNames;

  // // Close the file
  // NXclose(&fileId);

  // TODO. The HDF5/Nexus file structure is different from the workspace2D so
  // new implementation needed of above.
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
      do_test_workspace2d(filename);
      // do_test_event_workspace(filename);
    }
  }

  return result;
}
