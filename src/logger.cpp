#include "logger.hpp"

logger::logger() : iseol(true)
{
    std::string logfile = "log";
    this->stream.open(logfile, std::ofstream::out | std::ofstream::app);
    if (!this->stream)
    {
        std::cout << "WARNING: couldn't open " << logfile << " for writing; logging will be disabled" << std::endl;
        this->nolog = true;
    }
}

logger::~logger()
{
    if (!this->nolog)
        this->stream.close();
}
