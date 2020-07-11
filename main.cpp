#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <list>
#include "Worker.h"
int main(int argc, char* argv[])
{
    //Check if at least 2 arguments are provided
    if(argc < 3)
    {
        std::cout << "You need to specify the port and worker number !\n";
        return 1;
    }
    //Parse argument 1 as port
    const unsigned short port = std::stoi(argv[1]);
    //Parse argument 2 as number of worker threads
    const unsigned short worker_number = std::stoi(argv[2]);

    std::cout << "Starting server on port " << port << " with " << worker_number << " workers\n";
    //Listener socket
    sf::TcpListener listener{ };
    //Bind on specified port and check for success
    if(listener.listen(port) != sf::Socket::Done)
    {
        std::cout << "Error binding!\n";
        return 1;
    }

    //Vector of workers
    std::vector<http::Worker> workers(worker_number);
    //Give each worker an ID
    for(int i = 0; i < worker_number; i++)
    {
        workers.at(i).id = i + 1;
    }
    //list of clients
    std::list<std::unique_ptr<sf::TcpSocket>> clients;
    //Main loop
    while(true)
    {
        //Create smart pointer to connection
        auto client = std::make_unique<sf::TcpSocket>();
        //Accept client
        listener.accept(*client);
        //you gotta wait till it's time for you :D
        clients.push_back(std::move(client));
        //Go through each worker till the client list is empty
        for (std::size_t i = 0; i < workers.size() && !clients.empty(); i++)
        {
            if (workers[i].isAvailable())
            {
                //Move client to worker
                workers[i].assign(std::move(clients.front()));
                clients.pop_front();
            }
        }
    }
}
