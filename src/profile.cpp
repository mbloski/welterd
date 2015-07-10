#include "profile.hpp"

Profile::Profile()
{
    this->reload();
}

void Profile::reload()
{
    if (access("device_id", R_OK) == -1)
    {
        std::ofstream ofdevice_id;
        ofdevice_id.open("device_id");
        ofdevice_id.close();
    }
    
    if (access("profile", R_OK) == -1)
    {
        std::ofstream ofprofile;
        ofprofile.open("profile");
        ofprofile.close();
    }
    
    std::ifstream ifdevice_id("device_id");
    std::ifstream ifprofile("profile");

    if (access("device_id", R_OK) == -1 || access("profile", R_OK) == -1)
    {
        std::cout << "ERROR: Make sure the following files:\n"
                   + util::get_workdir() + "/device_id\n"
                   + util::get_workdir() + "/profile\n"
                   << "have appropriate read/write permissions and try again." << std::endl;
        exit(1);
    }

    std::getline(ifdevice_id, this->device_id);
    std::getline(ifprofile, this->user_key);
    std::getline(ifprofile, this->secret);

    ifdevice_id.close();
    ifprofile.close();
    
    if (this->user_key.empty() || this->secret.empty()) {
        this->status = ProfileStatus::STATUS_NOINIT;
    } else if (this->device_id.empty()) {
        this->status = ProfileStatus::STATUS_NODEVICE;
    } else {
        this->status = ProfileStatus::STATUS_OK;
    }
}

std::string Profile::get_device_id() const
{
    return this->device_id;
}

std::string Profile::get_user_key() const
{
    return this->user_key;
}

std::string Profile::get_secret() const
{
    return this->secret;
}

ProfileStatus Profile::get_status() const
{
    return this->status;
}

Profile::~Profile()
{

}
