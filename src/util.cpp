#include "util.hpp"

std::string util::get_homedir()
{
    std::string ret;
    if ((ret = getenv("HOME")).empty())
    {
        /* if getenv() fails, try getpwuid() as the last resort. */
        ret = getpwuid(getuid())->pw_dir;
    }

    return ret;
}

std::string util::get_workdir()
{
    // FIXME: free it
    return getcwd(NULL, 0);
}

std::string util::get_timestamp()
{
    std::chrono::system_clock::time_point time_now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(time_now);
    tm local_tm = *localtime(&time);

    std::stringstream ret;
    ret << local_tm.tm_mon + 1
        << "/"
        << local_tm.tm_mday
        << "/"
        << local_tm.tm_year + 1900
        << " "
        << std::setfill('0') << std::setw(2) << local_tm.tm_hour
        << ":"
        << std::setfill('0') << std::setw(2) << local_tm.tm_min
        << ":"
        << std::setfill('0') << std::setw(2) << local_tm.tm_sec;

    return ret.str();
}

std::string util::replace(std::string source, const std::string &from, const std::string &to)
{
    int len, loop = 0;
    std::string ret = "", let;
    len = source.length();
    len--;
    while (loop <= len)
    {
        let = source.substr(loop, 1);
        if (let == from)
        {
            ret = ret + to;
        }
        else
        {
            ret = ret + let;
        }
        loop++;
    }

    return ret;
}

void util::urlencode(std::string &str)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = str.begin(), n = str.end(); i != n; ++i)
    {
        std::string::value_type c = (*i);

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            escaped << c;
            continue;
        }

        escaped << '%' << std::setw(2) << int((unsigned char) c);
    }

    str = escaped.str();
}

void util::htmlspecialchars(std::string &str)
{
    std::string buf;
    buf.reserve(str.size());
    for (size_t pos = 0; pos != str.size(); ++pos)
    {
        switch (str[pos])
        {
        case '&':
            buf.append("&amp;");
            break;
        case '\"':
            buf.append("&quot;");
            break;
        case '\'':
            buf.append("&apos;");
            break;
        case '<':
            buf.append("&lt;");
            break;
        case '>':
            buf.append("&gt;");
            break;
        default:
            buf.append(&str[pos], 1);
            break;
        }
    }

    str.swap(buf);
}
