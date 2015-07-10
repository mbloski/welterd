#ifndef __PROFILE_HPP_INCLUDED
#define __PROFILE_HPP_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

#include "util.hpp"

enum ProfileStatus
{
    STATUS_OK,
    STATUS_NODEVICE,
    STATUS_NOINIT
};

class Profile
{
public:
    Profile();
    ~Profile();
    
    void reload();
    
    std::string get_device_id() const;
    std::string get_user_key() const;
    std::string get_secret() const;
    ProfileStatus get_status() const;
  
private:
    ProfileStatus status;
    
    std::string device_id = "";
    std::string user_key = "";
    std::string secret = "";
};

#endif // __PROFILE_HPP_INCLUDED