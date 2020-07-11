#include <SFML/Network.hpp>
#include <cstdio>
#include <string>
#include <mutex>
#include "HTTParser.h"
#include "Worker.h"
#include <cstring>
#include <iostream>
namespace http
{
    Worker::Worker() : m_thread([this]()
    {
        char buffer[2048];
        std::unique_lock lock{ cond_mutex };
        sf::SocketSelector selector{ };
        while(true)
        {
            // Wait for assign to notify_one()
            cond_var.wait(lock, [this] () -> bool { return signaller; });
            // Exit while if not running, i.e. stop has been called
            if(!running) break;
            //Disable availability
            available = false;

            selector.add(*m_client);

            std::size_t sent;
            // Give the client a millisecond to send data
            if(selector.wait(sf::milliseconds(1)))
            {
                std::size_t received;
                m_client->receive(buffer, 2048, received);;
                Request request = Request::parse(std::string_view(buffer, received));
                if(request.error())
                {
                    std::string response = "HTTP/1.1 400 Bad HTTParser\r\n\r\n";
                    m_client->send(response.data(), response.size() + 1, sent);
                } else
                {
                    //std::string response = Response::response(request);
                    std::cout << "Parsed request without errors\n!";
                    const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf8\r\nContent-Length: 13\r\n\r\nHello World!";
                    std::cout << "Sending:\n" << response;
                    m_client->send(response, std::strlen(response), sent);

                }
            }
            else
            {
                std::string response = "HTTP/1.1 408 Request Timeout\r\n\r\n";
                m_client->send(response.data(), response.size() + 1, sent);
            }
            selector.clear();
            m_client.reset(nullptr);
            m_client = nullptr;            //Make Worker available again
            available = true;
            signaller = false;
        }
    }) { }

    void Worker::assign(std::unique_ptr<sf::TcpSocket>&& client) noexcept
    {
        //Shouldn't be needed at this point
        if (available)
        {
            // std::cout << "Worker " << id << " moving " << client.get() << " managed by " << &client << " to object " << &m_client << '\n';
            m_client = std::move(client);
            std::lock_guard lock{ cond_mutex };
            signaller = true;
            cond_var.notify_one();
        }
    }

    void Worker::stop() noexcept
    {
        std::lock_guard lock{ cond_mutex };
        running = true;
        cond_var.notify_one();
        m_thread.join();
    }


}