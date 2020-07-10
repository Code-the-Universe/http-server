#include "Worker.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <mutex>
namespace http
{
    Worker::Worker() : m_thread([this]()
    {
        std::unique_lock lock{ cond_mutex };
        while(true)
        {
            // Wait for assign to notify_one()
            cond_var.wait(lock, [this] () -> bool { return signaller; });
            // Exit while if not running, i.e. stop has been called
            if(!running) break;

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
            available = true;
            signaller = false;
        }
    }) { }

    void Worker::assign(std::unique_ptr<sf::TcpSocket>&& client) noexcept
    {
        //Shouldn't be needed at this point
        if (available)
        {
            //std::cout << "Assigning " << client.get() << " managed by " << &client << " to object " << &m_client << '\n';
            m_client = std::move(client);
            std::lock_guard lock{ cond_mutex };
            signaller = true;
            cond_var.notify_one();
        }
    }

    void Worker::stop() noexcept
    {
        running = false;
        m_thread.join();
    }


}