#include "HTTParser.h"
#include <string>
#include <iostream>
namespace http
{
    Request Request::parse(std::string_view request) noexcept
    {
        Request return_val;
        return_val.m_request = request;
        // Parse request method
        //Minimal workable request 'GET / HTTP/1.1\r\n\r\n' -> 18 characters
        if (request.size() < 18)
        {
            return_val.parse_error = true;
            return return_val;
        }
        const char * pos = request.data();
        //Extremely ugly but fast, every case is very self-explanatory
        return_val.m_method = [&]() -> int {
            switch (*pos)
            {
                case 'G':
                {
                    if (*(pos + 1) == 'E' && *(pos + 2) == 'T')
                    {
                        pos += 3;
                        return GET;
                    }
                    return -1;
                }
                case 'P':
                {
                    if (*(pos + 1) == 'O' && *(pos + 2) == 'S' && *(pos + 3) == 'T')
                    {
                        pos += 4;
                        return POST;
                    }
                    if (*(pos + 1) == 'U' && *(pos + 2) == 'T')
                    {
                        pos += 3;
                        return PUT;
                    }
                    if (*(pos + 1) == 'A' && *(pos + 2) == 'T' && *(pos + 3) == 'C' && *(pos + 4) == 'H')
                    {
                        pos += 5;
                        return PATCH;
                    }
                    return -1;
                }
                case 'H':
                {
                    if (*(pos + 1) == 'E' && *(pos + 2) == 'A' && *(pos + 3) == 'D')
                    {
                        pos += 4;
                        return HEAD;
                    }
                    return -1;
                }
                case 'T':
                {
                    if (*(pos + 1) == 'R' && *(pos + 2) == 'A' && *(pos + 3) == 'C' && *(pos + 4) == 'E')
                    {
                        pos += 5;
                        return TRACE;
                    }
                    return -1;
                }
                case 'D':
                {
                    if (*(pos + 1) == 'E' && *(pos + 2) == 'L' && *(pos + 3) == 'E' && *(pos + 4) == 'T' && *(pos + 5) == 'E')
                    {
                        pos += 6;
                        return DELETE;
                    }
                    return -1;
                }
                case 'C':
                {
                    if (*(pos + 1) == 'O' && *(pos + 2) == 'N' && *(pos + 3) == 'N' && *(pos + 4) == 'E' && *(pos + 5) == 'C' && *(pos + 6) == 'T')
                    {
                        pos += 7;
                        return CONNECT;
                    }
                    return -1;
                }
                case 'O':
                {
                    if (*(pos + 1) == 'P' && *(pos + 2) == 'T' && *(pos + 3) == 'I' && *(pos + 4) == 'O' && *(pos + 5) == 'N' && *(pos + 6) == 'S')
                    {
                        pos += 7;
                        return OPTIONS;
                    }
                    return -1;
                }
                default: return -1;
            }
        }();
        return return_val;

    }
}