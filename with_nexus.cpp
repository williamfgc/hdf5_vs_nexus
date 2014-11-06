#include <nexus/NeXusFile.hpp>
#include <nexus/NeXusException.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "process_args.h"
#include "timer.h"
#include <map>

using common::Timer;
using std::string;
using std::map;
using std::vector;

static const string NULL_STR("NULL");
static const string NX_EVENT_DATA("NXevent_data");

std::string read_string_data(NeXus::File &file, const std::string &path) {
  std::string result;
  file.readData(path, result);

  return result;
}

template <typename NumT>
std::vector<NumT> read_data(NeXus::File &file,
                            const std::string &path) {
  std::vector<NumT> vec;
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
  read_data<double>(file, "values");

  // // Open errors
  read_data<double>(file, "errors");

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
  file.openGroup("entry", "NXentry");

  // get a list of all NXevent_data
  vector<string> eventDataNames;
  size_t numFields = 0;
  if (false) { // get a map and process it
    map<string, string> entries = file.getEntries();
    for (map<string, string>::const_iterator it = entries.begin();
         it != entries.end(); ++it) {
      ++numFields;
      if (it->second == NX_EVENT_DATA) {
        eventDataNames.push_back(it->first);
      }
    }
  } else {
    std::pair<string, string> temp;
    while (true) {
      temp = file.getNextEntry();
      if (temp.first == NULL_STR &&
          temp.second == NULL_STR) { // TODO this needs to be changed when
                                     // getNextEntry is fixed
        break;
      } else if (temp.second == NX_EVENT_DATA) {
        eventDataNames.push_back(temp.first);
      }
    }
  }
  // std::cout << "numEventData " << eventDataNames.size() << " of " <<
  // numFields << std::endl;

  for (  vector<string>::const_iterator it = eventDataNames.begin(); it != eventDataNames.end(); ++it){
    file.openGroup(*it, NX_EVENT_DATA);
    // NX Data  : event_id (NX_UINT32) - index int pulse_id
    read_data<uint32_t>(file, "event_id");
    // NX Data  : event_index (NX_UINT64) - pixel_id per event?
    read_data<uint64_t>(file, "event_index");
    // NX Data  : event_time_offset (NX_FLOAT32) - pulse_id
    read_data<float>(file, "event_time_offset");
    // NX Data  : event_time_zero (NX_FLOAT64) - tof
    read_data<double>(file, "event_time_zero");
    // NX Data  : pixel_id[8,128] (NX_UINT32)
    // NX Data  : total_counts (NX_UINT32)

    file.closeGroup();
  }

  file.closeGroup();
  file.close();

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
