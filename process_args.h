#ifndef _PROCESS_ARGS_H
#define _PROCESS_ARGS_H

#include <string>

namespace common
{
    void print_usage(const std::string & prog);
    std::string to_filename(const std::string & name);
}

#endif // _PROCESS_ARGS_H
