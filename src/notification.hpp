#ifndef __NOTIFICATION_HPP_INCLUDED
#define __NOTIFICATION_HPP_INCLUDED

#include <libnotify/notify.h>
#include <string>

#include "util.hpp"

class PushNotification
{
public:
    PushNotification();
    PushNotification(std::string title, std::string url = "");
    ~PushNotification();

    PushNotification &operator=(const char *message);

    bool push();

    std::string title;
    std::string message;
    std::string icon;
    std::string url;

private:
    NotifyNotification *libnotify_notification;
    bool pushed;
};

#endif // __NOTIFICATION_HPP_INCLUDED
