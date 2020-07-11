#include "HTTParser.h"
namespace http
{
    std::string Response::response(const Request & ) noexcept
    {
        return "HTTP/1.1 501 Not Implemented\r\n\r\n";
    }
}