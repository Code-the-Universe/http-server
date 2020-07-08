#include "Worker.h"
namespace http
{
    Worker::Worker(unsigned int worker_id) : m_thread([this]()
    {
        while(running)
        {
            // DO STUFF
        }
    }), id(worker_id) { }

    void Worker::stop() noexcept
    {
        running = false;
        m_thread.join();
    }
}