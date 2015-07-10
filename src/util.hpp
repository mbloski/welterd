#ifndef __UTIL_HPP_INCLUDED
#define __UTIL_HPP_INCLUDED

#include <unistd.h>
#include <pwd.h>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>

namespace util
{
std::string get_homedir();
std::string get_workdir();
std::string get_timestamp();
std::string replace(std::string source, const std::string &from, const std::string &to);
void urlencode(std::string &value);
void htmlspecialchars(std::string &data);
};

#endif // __UTIL_HPP_INCLUDED
