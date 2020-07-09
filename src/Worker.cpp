#include "Worker.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace http
{
    Worker::Worker() : m_thread([this]()
    {
        while(running)
        {
            if(signaller)
            {
                available = false;
                char data[1024];
                int response = recv(m_client, data, 1024, 0);
                if (response > 0)
                {
                    std::string msg = "HTTP/1.1 200 OK\nHello!";
                    int bytes_sent = send(m_client, msg.c_str(), msg.size(), 0);
                    if (bytes_sent > 0)
                    {
                        close(m_client);
                    }
                }
                else if (response == 0)
                {
                    //close
                    close(m_client);
                }
                m_client = -1;
                available = true;
                signaller = false;
            }
        }
    }) { }

    void Worker::assign(int client) noexcept
    {
        //Shouldn't be needed at this point
        if (available)
        {
            m_client = client;
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
