#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <list>
#include <memory>
#include <mutex>
#include "Worker.h"
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        std::cout << "You need to specify the port and worker number !\n";
        std::exit(1);
    }
    const unsigned short port = std::atoi(argv[1]);
    const unsigned short worker_number = std::atoi(argv[2]);
    std::cout << "Starting server on port " << port << " with " << worker_number << " workers\n";
    sf::TcpListener listener{ };
    if(listener.listen(port) != sf::Socket::Done)
    {
        std::cout << "Error binding!\n";
        std::exit(1);
    }
    std::mutex client_mutex;
    std::list<std::unique_ptr<sf::TcpSocket>> clients;
    std::thread handler{[&]{
        std::vector<http::Worker> workers(worker_number);
        for(int i = 0; i < worker_number; i++)
        {
            workers.at(i).id = i + 1;
        }
        while(true)
        {
            std::lock_guard lockGuard{ client_mutex };
            while(!clients.empty())
            {
                //std::cout << "Queue is not empty, querying workers\n";
                for(auto& worker : workers)
                {
                    if (worker.isAvailable())
                    {
                        //std::cout << "Worker " << worker.id << " available!\n";
                        worker.assign(std::move(clients.front()));
                        clients.pop_front();
                        //Very important, its absence would cause a segfault
                        break;
                    }
                }
            }
        }
    }};
    while(true)
    {
        auto client = std::make_unique<sf::TcpSocket>();
        listener.accept(*client);
        //std::cout << "Accepted client from: " << client->getRemoteAddress() << '\n';
        std::lock_guard lockGuard{ client_mutex };
        clients.push_back(std::move(client));
        //std::cout << "Pushed client to queue! \n";
    }
}
