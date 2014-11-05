#include <nexus/NeXusFile.hpp>
#include <nexus/NeXusException.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "process_args.h"
#include "timer.h"

using common::Timer;

std::string read_string_data(NeXus::File &file, const std::string &path) {
  std::string result;
  file.readData(path, result);

  return result;
}

std::vector<double> read_double_data(NeXus::File &file,
                                     const std::string &path) {
  std::vector<double> vec;
  file.readData(path, vec);

  return vec;
}

void do_test_workspace2d(const std::string &filename) {
  Timer timer;
  timer.reset();

  NeXus::File file(filename);

  // Open the workspace group
  file.openGroup("mantid_workspace_1", "NXentry");

  read_string_data(file, "instrument/instrument_xml/data");

  // Open the workspace entry
  file.openGroup("workspace", "NXdata");

  // // Open values
  read_double_data(file, "values");

  // // Open errors
  read_double_data(file, "errors");

  // // Close the groups
  file.closeGroup();
  file.closeGroup();

  // // Close the file
  file.close();

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
