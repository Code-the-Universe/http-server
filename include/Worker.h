#ifndef HTTP_WORKER_H
#define HTTP_WORKER_H
#include <thread>
#include <atomic>
#include <memory>

namespace http
{

    class Worker
    {
        std::atomic_bool running = true;
        std::atomic_bool available = true;
        std::atomic_bool signaller = false;
        std::thread m_thread;
        int m_client = -1;
    public:
        unsigned int id;

        Worker();
        void assign(int) noexcept;

        void stop() noexcept;
        bool isAvailable() noexcept { return available; };

    };
}
#endif //HTTP_WORKER_H
