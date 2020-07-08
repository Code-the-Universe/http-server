#ifndef HTTP_WORKER_H
#define HTTP_WORKER_H
#include <thread>
#include <atomic>
#include <SFML/Network.hpp>

namespace http
{

    class Worker
    {
        std::atomic_bool running = true;
        std::thread m_thread;

    public:
        const unsigned int id;

        Worker(unsigned int worker_id);
        void stop() noexcept;
    };
}
#endif //HTTP_WORKER_H
