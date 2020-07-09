#include "Worker.h"
#include <cstdio>
#include <string>
#include <iostream>
namespace http
{
    Worker::Worker() : m_thread([this]()
    {
        while(running)
        {
            if(signaller)
            {
                available = false;
                char buffer[2048];
                // std::cout << "Worker number " << id << " working on client object " << m_client.get() << '\n';
                std::size_t received;
                m_client->receive(buffer, 2048, received);
                // std::cout << "Received " << received << " characters:\n";
                // std::cout.write(buffer, received);
                std::string response = "Hello There!";
                std::size_t sent;
                m_client->send(response.data(), response.size() + 1, sent);
                // std::cout << "Sent " << sent << " characters\n";
                m_client.reset();
                m_client = nullptr;
                available = true;
                signaller = false;
            }
        }
    }) { }

    void Worker::assign(std::unique_ptr<sf::TcpSocket>&& client) noexcept
    {
        //Shouldn't be needed at this point
        if (available)
        {
            m_client = std::move(client);
            // std::cout << "Assigned client in worker " << id << " with client " << client.get() << " moved to " << m_client.get() << '\n';
            signaller = true;
        }
    }

    void Worker::stop() noexcept
    {
        running = false;
        m_thread.join();
    }


}