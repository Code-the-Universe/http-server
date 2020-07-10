#ifndef HTTP_WORKER_H
#define HTTP_WORKER_H
#include <SFML/Network.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
namespace http
{

    class Worker
    {
        //Concurrency stuff

        //Controls running of worker
        std::atomic_bool            running     = true;
        //Signals availability
        std::atomic_bool            available   = true;
        //Used as bool for the conditional_variable
        std::atomic_bool            signaller   = false;
        //conditional variable as not to busy wait
        std::condition_variable     cond_var;
        //mutex for c_v
        std::mutex                  cond_mutex;
        //thread worker is running on
        std::thread                 m_thread;

        //client pointer
        std::unique_ptr<sf::TcpSocket> m_client { nullptr };
    public:
        //Worker ID
        unsigned int id;

        //Constructor - sets the worker running
        Worker();
        //assigns the client
        void assign(std::unique_ptr<sf::TcpSocket>&&) noexcept;

        //stops the worker
        void stop() noexcept;
        //signals availability
        bool isAvailable() noexcept { return available; };
    };
}
#endif //HTTP_WORKER_H
