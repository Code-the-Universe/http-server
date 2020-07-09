#ifndef HTTP_WORKER_H
#define HTTP_WORKER_H
#include <thread>
#include <atomic>
#include <memory>
#include <SFML/Network.hpp>

namespace http
{

    class Worker
    {
        std::atomic_bool running = true;
        std::atomic_bool available = true;
        std::atomic_bool signaller = false;
        std::thread m_thread;
        std::unique_ptr<sf::TcpSocket> m_client = nullptr;
    public:
        unsigned int id;

        Worker();
        void assign(std::unique_ptr<sf::TcpSocket>&&) noexcept;

        void stop() noexcept;
        bool isAvailable() noexcept { return available; };

    };
}
#endif //HTTP_WORKER_H
