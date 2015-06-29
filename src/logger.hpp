#ifndef __LOGGER_HPP_INCLUDED
#define __LOGGER_HPP_INCLUDED

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

#include "util.hpp"

class logger
{
public:
    logger();
    ~logger();

    inline logger &operator<<(std::ostream & (*data)(std::ostream &)) {
        std::cout << data;
        this->stream << data;

        /* oh dear... */
        if (data == (std::basic_ostream<char> &( *)(std::basic_ostream<char> &)) &std::endl) {
            iseol = true;
        }

        return *this;
    }

    template <typename T> logger &operator<<(const T &data) {
        if (iseol) {
            std::string header = util::get_timestamp() + "  --  ";
            std::cout << header;
            this->stream << header;
            iseol = false;
        }
        std::cout << data;
        this->stream << data;
    }

private:
    std::ofstream stream;
    bool nolog;
    bool iseol;
};

#endif // __LOGGER_HPP_INCLUDED
