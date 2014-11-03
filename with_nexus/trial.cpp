#include <nexus/napi.h>
#include <string>
#include <iostream>
#include "timer.h"
#include "Poco/Path.h"

using common::Timer;

int main()
{

  Timer timer;
  timer.start();

  NXhandle fileId;
  Poco::Path file_path("../common/INTER00013460.nxs");
  const std::string sFile_path = file_path.absolute().toString();
  std::cout << sFile_path << std::endl;
  NXstatus stat=NXopen(sFile_path.c_str(), NXACC_READ, &fileId);

  // Open the workspace group
  std::string path = "mantid_workspace_1";
  NXopengroup( fileId, path.c_str(), "NXentry");

  // Open the workspace entry
  path = "workspace";
  NXopengroup( fileId, path.c_str(), "NXdata");

  // Open values
  path = "values";
  NXopendata( fileId, path.c_str());

  // Open errors
  path = "errors";
  NXopendata( fileId, path.c_str());

  // Stop
  timer.stop();
  std::cout << "Elapsed time in ms: " << timer.elapsed_ms() <<  std::endl;

}
