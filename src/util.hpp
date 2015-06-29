#ifndef __UTIL_HPP_INCLUDED
#define __UTIL_HPP_INCLUDED

#include <unistd.h>
#include <pwd.h>
#include <string>
#include <chrono>
#include <sstream>

namespace util
{
std::string get_homedir();
std::string get_workdir();
std::string get_timestamp();
};

#endif // __UTIL_HPP_INCLUDED
