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
        int m_method;
        //indicates an error during the parsing stage
        bool parse_error;
        std::string_view m_request;
        public:
        // Parse request
        static Request parse(std::string_view) noexcept;

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
         inline int method() const noexcept { return m_method; }
         inline bool error() const noexcept { return parse_error; }
         inline std::string_view response_text() const noexcept { return m_request; }
    };
    // Class representing an HTTP response
    class Response
    {
    public:
        static std::string response(const Request&) noexcept;
    };
}
#endif
