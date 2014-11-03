#include <nexus/napi.h>
#include <string>
#include <iostream>
#include <vector>
#include "timer.h"
#include "Poco/Path.h"

using common::Timer;

std::string read_string_data(NXhandle& fileId, const std::string& path)
{
  int rank;
  int dims[4];
  int type;
  NXopendata(fileId, path.c_str());
  NXgetinfo(fileId, &rank, dims, &type);
  int n = dims[0];
  char* buffer = new char[n];
  NXstatus stat = NXgetdata(fileId, buffer);
  NXclosedata(fileId);
  return std::string(buffer);
}

std::vector<double> read_double_data(NXhandle& fileId, const std::string& path)
{
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

int main()
{

  Timer timer;
  timer.start();

  NXhandle fileId;
  Poco::Path file_path("../common/INTER00013460.nxs");
  const std::string sFile_path = file_path.absolute().toString();
  std::cout << sFile_path << std::endl;
  NXstatus stat = NXopen(sFile_path.c_str(), NXACC_READ, &fileId);

  // Open the workspace group
  std::string path = "mantid_workspace_1";
  NXopengroup(fileId, path.c_str(), "NXentry");

  path = "instrument/instrument_xml/data";

  // Open the workspace entry
  path = "workspace";
  NXopengroup(fileId, path.c_str(), "NXdata");

  // Open values
  path = "values";
  read_double_data(fileId, path.c_str());

  // Open errors
  path = "errors";
  read_double_data(fileId, path.c_str());

  // Close the groups
  NXclosegroup(fileId);
  NXclosegroup(fileId);

  // Close the file
  NXclose(&fileId);

  // Stop
  timer.stop();
  std::cout << "Elapsed time in ms: " << timer.elapsed_ms() << std::endl;

}
