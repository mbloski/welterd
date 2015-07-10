#include "api.hpp"

static int write_function(char *data, size_t size, size_t nmemb, std::string *buf)
{
    int ret = 0;
    if (buf != NULL)
    {
        buf->append(data, size * nmemb);
        ret = size * nmemb;
    }
    
    return ret;
}

API::API(Profile *profile)
{
    this->profile = profile;
    this->curl = curl_easy_init();
}

API::~API()
{
    curl_easy_cleanup(this->curl);
}

std::string API::generic_curl_request(std::string uri, std::string params)
{
    std::string ret;
    CURLcode res;

    curl_easy_setopt(this->curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(this->curl, CURLOPT_USERAGENT, "welterd/0.1");
    if (!params.empty())
    {
        curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, params.c_str());
    }
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, write_function);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &ret);

    res = curl_easy_perform(this->curl);
    return ret;
}

std::string API::login(std::string email, std::string password)
{
    return this->generic_curl_request("https://api.pushover.net/1/users/login.json", "email=" + email + "&password=" + password);
}

std::string API::register_device(std::string name)
{
    return this->generic_curl_request("https://api.pushover.net/1/devices.json", "secret=" + this->profile->get_secret() + "&name=" + name + "&os=O");
}

std::string API::fetch_messages()
{
    curl_easy_setopt(this->curl, CURLOPT_POST, 0);
    return this->generic_curl_request("https://api.pushover.net/1/messages.json?secret=" + this->profile->get_secret() + "&device_id=" + this->profile->get_device_id());
}

std::string API::delete_message(int message)
{
    return this->generic_curl_request("https://api.pushover.net/1/devices/" + this->profile->get_device_id() + "/update_highest_message.json", "secret=" + this->profile->get_secret() + "&message=" + std::to_string(message));
}