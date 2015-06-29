#include "util.hpp"

std::string util::get_homedir()
{
    std::string ret;
    if ((ret = getenv("HOME")).empty()) {
	/* if getenv() fails, try getpwuid() as the last resort. */
        ret = getpwuid(getuid())->pw_dir;
    }

    return ret;
}

std::string util::get_workdir()
{
    // FIXME: free it
    return getcwd(NULL, 0);
}

std::string util::get_timestamp()
{
    std::chrono::system_clock::time_point time_now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(time_now);
    tm local_tm = *localtime(&time);

    std::stringstream ret;
    ret << local_tm.tm_mon + 1
        << "/"
        << local_tm.tm_mday
        << "/"
        << local_tm.tm_year + 1900
        << " "
        << std::setfill('0') << std::setw(2) << local_tm.tm_hour
        << ":"
        << std::setfill('0') << std::setw(2) << local_tm.tm_min
        << ":"
        << std::setfill('0') << std::setw(2) << local_tm.tm_sec;

    return ret.str();
}
