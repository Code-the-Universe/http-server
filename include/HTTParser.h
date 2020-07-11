#ifndef HTTP_HTTPARSER_H
#define HTTP_HTTPARSER_H
#include <string>
#include <map>
namespace http
{
    // Class representing HTTP request
    class Request
    {
        // request method
        unsigned int m_method;

        public:
        // Parse request
        static Request parse(std::string_view);

        // Method enumerations
        enum
        {
            GET,
            HEAD,
            POST,
            PUT,
            DELETE,
            CONNECT,
            OPTIONS,
            TRACE,
            PATCH
        };

        /**
         * Actual instance info
         */
         inline unsigned int method() { return m_method; }

    };
}
#endif
