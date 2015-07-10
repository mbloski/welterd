#include <iostream>
#include <unistd.h>
#include <gtk/gtk.h>
#include <json/json.h>
#include <algorithm>
#include <termios.h>

#include "api.hpp"
#include "logger.hpp"
#include "notification.hpp"
#include "profile.hpp"
#include "util.hpp"

void env_prepare()
{
    notify_init("Pushover");
    curl_global_init(CURL_GLOBAL_DEFAULT);

    std::string workdir = util::get_homedir() + "/.welterd";
    if (chdir(workdir.c_str()) != 0)
    {
        std::cout << "error: couldn't set working directory to \"" << workdir << "\"" << std::endl;
        exit(1);
    }
    else
    {
        //std::cout << "residing in " << workdir << std::endl;
    }
}

void login_wizard(Profile *profile, API *api)
{
    std::cout << "Welcome! You need to login in order to use welterd." << std::endl;
    std::string email;
    std::string password;
    
    for (uint8_t i = 0; i < 3; ++i)
    {
        std::cout << "  e-mail: ";
        std::getline(std::cin, email);
        std::cout << "password: ";
        
        termios tty;
        tcgetattr(STDIN_FILENO, &tty);
        tty.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);
        std::getline(std::cin, password);
        tty.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);
        
        std::cout << "(hidden)\n";
        
        std::string res = api->login(email, password);
        
        Json::Value json;
        Json::Reader reader;
        reader.parse(res, json);
        
        if (json["status"].asInt() != 1)
        {
            std::cout << "ERROR: Wrong e-mail or password" << std::endl;
        }
        else
        {
            std::string user_key = json["id"].asString();
            std::string secret = json["secret"].asString();
            
            std::ofstream ofprofile;
            ofprofile.open("profile", std::ofstream::out);
            if (!ofprofile)
            {
                std::cout << "ERROR: cannot save to " << util::get_workdir() + "/profile\n"
                          << "You can manually save these lines to the file to continue:\n\n"
                          << user_key << "\n" << secret << "\n" << std::endl;
                return;
            }
            
            ofprofile << user_key + "\n" + secret;
            ofprofile.close();
            
            return;
        }
    }
    
    std::cout << "ERROR: Take a break" << std::endl;
    exit(1);
}

void device_wizard(Profile *profile, API *api)
{
    std::cout << "This device hasn't been registered yet. Let's do this now." << std::endl;
    
    while(true)
    {
        std::cout << "What to name this device? (up to 25 characters long): ";

        std::string device_name;
        std::getline(std::cin, device_name);
        // TODO: [A-Za-z0-9_-]
        device_name = device_name.substr(0, 25);
        util::urlencode(device_name);

        std::string res = api->register_device(device_name);

        Json::Value json;
        Json::Reader reader;
        reader.parse(res, json);

        if (json["status"].asInt() != 1)
        {
            std::string nameerror = json["errors"]["name"][0].asString(); // FIXME: this isn't the safest...
            // TODO: handle errors better
            if (!nameerror.empty())
            {
                std::cout << "Error: name " << nameerror << std::endl;
            }
            else
            {
                std::string errstr = json["message"].asString();
                if (errstr.empty())
                {
                    errstr = "unknown";
                }
                std::cout << "Error: " << errstr << std::endl;
            }
            
            if (nameerror == "has already been taken")
            {
                std::cout << "If you want to reuse this name, go to http://pushover.net/ and delete the matching device." << std::endl;
            }
        }
        else
        {
            std::string device_id = json["id"].asString();
            std::ofstream ofdevice_id;
            ofdevice_id.open("device_id", std::ofstream::out);
            if (!ofdevice_id)
            {
                std::cout << "ERROR: cannot save to " << util::get_workdir() + "/device_id\n"
                          << "You can manually save this line to the file to continue:\n\n"
                          << device_id << "\n" << std::endl;
                exit(1);
            }
            ofdevice_id << device_id;
            ofdevice_id.close();
            
            std::cout << "Congratulations. Your profile is now complete and ready to receive notifications." << std::endl;
            return;
        }
    }
}

int main(int argc, char **argv)
{
    env_prepare();
    Profile profile;
    API pushover_api(&profile);

    if (profile.get_status() == ProfileStatus::STATUS_NOINIT)
    {
        login_wizard(&profile, &pushover_api);
        profile.reload();
    }
    
    if (profile.get_status() == ProfileStatus::STATUS_NODEVICE)
    {
        device_wizard(&profile, &pushover_api);
        profile.reload();
    }

    // TODO: parse argv (--version -v, --reset -r)

    std::cout << "welterd is starting up" << std::endl;
    logger mainlog;

    //std::cout << "forking into background..." << std::endl;
    //daemon(1, 0);

    // This is just a test.
    Json::Value ret;
    Json::Reader reader;
    reader.parse(pushover_api.fetch_messages(), ret);

    Json::Value list = ret["messages"];
    for (Json::ValueIterator i = list.begin(); i != list.end(); ++i)
    {
        std::string message = i->get("message", "").asString();
        std::string title = i->get("title", "").asString();
        std::string url = i->get("url", "").asString();

        PushNotification n;
        n.title = title;
        n.url = url;
        n.message = message;
        n.push();
    }

    mainlog << "test" << std::endl;

    /*while (true)
    {
      gtk_main_iteration();

    }*/

    curl_global_cleanup();
    return 0;
}
