#ifndef __API_HPP_INCLUDED
#define __API_HPP_INCLUDED

#include <string>
#include <curl/curl.h>

#include "profile.hpp"

class API
{
public:
    API(Profile *profile);
    ~API();

    std::string login(std::string email, std::string password);
    std::string register_device(std::string name);
    std::string fetch_messages();
    std::string delete_message(int message);

private:
    std::string generic_curl_request(std::string uri, std::string params = "");

    Profile *profile;
    CURL *curl;
};

#endif // __API_HPP_INCLUDED
