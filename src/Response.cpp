#include "HTTParser.h"
namespace http
{
    std::string Response::response(const Request & request) noexcept
    {
        auto requ = request.response_text();
        std::string response = "HTTP/1.1 200 OK\r\nContent-Length:";
        response += requ.length();
        response += "\r\nContent-Type: text/plain; charset=utf8\r\n";
        response += requ;
        response += "\r\n\r\n";
        return response;
    }
}