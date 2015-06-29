#include "notification.hpp"

void handle_url(NotifyNotification *notification, gchar *action, gpointer user_data)
{
    GError *error = NULL;
    g_app_info_launch_default_for_uri((const char *)user_data, NULL, &error);
}

PushNotification::PushNotification()
{
    this->title = "Push Notification";
}

PushNotification &PushNotification::operator=(const char *message)
{
    this->message = message;
    return *this;
}

void PushNotification::set_message(std::string message)
{
    this->operator=(message.c_str());
}

void PushNotification::set_icon(std::string icon)
{
    this->icon = icon;
}

PushNotification::PushNotification(std::string title, std::string url)
{
    this->title = title;
    this->url = url;
}

bool PushNotification::push()
{
    if (this->icon.empty()) {
        this->icon = util::get_workdir() + "/icons/pushover-icon.png";
    }

    this->libnotify_notification = notify_notification_new(this->title.c_str(), this->message.c_str(), this->icon.c_str());
    if (!this->url.empty()) {
        notify_notification_add_action(this->libnotify_notification, "default", "Open URL", (NotifyActionCallback)handle_url, (void *)this->url.c_str(), 0);
    }
    notify_notification_show(this->libnotify_notification, nullptr);
    this->pushed = true;
}

std::string PushNotification::get_message()
{
    return this->message;
}

PushNotification::~PushNotification()
{

}
