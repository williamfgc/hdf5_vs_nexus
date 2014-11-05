#include <iostream>
#include <Poco/Exception.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include "process_args.h"

namespace common {
void print_usage(const std::string &prog) {
  std::cout << "usage: " << prog << " <filename>"
            << "\n"
            << "\n"
            << "This will print out the elapsed time for each file in ms"
            << std::endl;
}

std::string to_filename(const std::string &name) {
  try {

    Poco::Path path(name);
    path = path.absolute();
    if (path.isFile()) {
      if (Poco::File(path).canRead()) {
        return path.toString();
      }
    }
  }
  catch (Poco::FileNotFoundException &e) {
    // let it drop on the floor
  }
  return "";
}
}