#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <list>
#include <memory>
#include <mutex>
#include "Worker.h"
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

    std::vector<http::Worker> workers(worker_number);
    for(int i = 0; i < worker_number; i++)
    {
        workers.at(i).id = i + 1;
    }
    while(true)
    {
        auto client = std::make_unique<sf::TcpSocket>();
        listener.accept(*client);
        [&] {
            while (true)
            {
                for (auto &worker : workers)
                {
                    if (worker.isAvailable())
                    {
                        worker.assign(std::move(client));
                        return;
                    }
                }
            }
        }();
    }
}
