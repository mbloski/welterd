#include <iostream>
#include <unistd.h>
#include <gtk/gtk.h>

#include "logger.hpp"
#include "notification.hpp"
#include "profile.hpp"
#include "util.hpp"

void env_prepare()
{
    notify_init("Pushover");

    std::string workdir = util::get_homedir() + "/.welterd";
    if (chdir(workdir.c_str()) != 0) {
        std::cout << "error: couldn't set working directory to \"" << workdir << "\"" << std::endl;
        exit(1);
    } else {
        std::cout << "residing in " << workdir << std::endl;
    }
}

void profile_wizard()
{
    std::cout << "It looks like this device hasn't been registered yet.\n"
              << "This wizard will create a new user prifile." << std::endl;
    // TODO: this
}

int main(int argc, char **argv)
{
    // TODO: parse argv (--setup -s)
    Profile prof("profile");

    std::cout << "welterd is starting up" << std::endl;
    env_prepare();
    logger mainlog;

    //std::cout << "forking into background..." << std::endl;
    //daemon(1, 0);

    PushNotification n;
    n = "test notification";
    n.push();

    mainlog << "test" << std::endl;

    /*while (true)
    {
      gtk_main_iteration();

    }*/

    return 0;
}
