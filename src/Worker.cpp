#include <SFML/Network.hpp>
#include <cstdio>
#include <string>
#include <mutex>
#include <iostream>
#include "Worker.h"
namespace http
{
    Worker::Worker() : m_thread([this]()
    {
        char buffer[2048];
        std::unique_lock lock{ cond_mutex };
        while(true)
        {
            // Wait for assign to notify_one()
            cond_var.wait(lock, [this] () -> bool { return signaller; });
            // Exit while if not running, i.e. stop has been called
            if(!running) break;
            //Disable availability
            available = false;

            sf::SocketSelector selector{ };
            selector.add(*m_client);

            std::size_t sent;
            // Give the client a millisecond to send data
            if(selector.wait(sf::milliseconds(1)))
            {
                std::size_t received;
                m_client->receive(buffer, 2048, received);;
                std::string response = "HTTP/1.1 501 Not Implemented\r\n";
                m_client->send(response.data(), response.size() + 1, sent);
            }
            else
            {
                std::string response = "HTTP/1.1 408 Request Timeout\r\n";
                m_client->send(response.data(), response.size() + 1, sent);
            }
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