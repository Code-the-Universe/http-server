#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <HTTParser.h>
TEST_CASE ("HTTParser parser")
{
    const std::string base = " / HTTP/1.1\r\n\r\n";
    auto r = http::Request::parse("GET" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::GET);

    r = http::Request::parse("HEAD" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::HEAD);

    r = http::Request::parse("POST" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::POST);

    r = http::Request::parse("PUT" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::PUT);

    r = http::Request::parse("DELETE" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::DELETE);

    r = http::Request::parse("CONNECT" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::CONNECT);

    r = http::Request::parse("OPTIONS" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::OPTIONS);

    r = http::Request::parse("TRACE" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::TRACE);

    r = http::Request::parse("DELETE" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::DELETE);

    r = http::Request::parse("PATCH" + base);
    REQUIRE(r.error() == false);
    REQUIRE(r.method() ==  http::Request::PATCH);
}
