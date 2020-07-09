#include <iostream>
#include <thread>
#include <vector>
//stuff
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <cstring>
#include <unistd.h>

#include "Worker.h"

//just a example func to handle a socket connection by int only
void handle(int socket)
{
    char data[1024];
    int response = recv(socket, data, 1024, 0);
    if (response > 0)
    {
        std::string msg = "HTTP/1.1 200 OK\nHello!";
        int bytes_sent = send(socket, msg.c_str(), msg.size(), 0);
        if (bytes_sent > 0)
        {
            close(socket);
        }
    }
    else if (response == 0)
    {
        //close
        close(socket);
    }
}

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
    //test stuff
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;          // will point to the results

    memset(&hints, 0, sizeof hints);    // make sure the struct is empty
    hints.ai_family = AF_INET;          //IP4
    hints.ai_socktype = SOCK_STREAM;    //TCP stream sockets
    hints.ai_flags = AI_PASSIVE;        //fill in my IP for me OwO

    if ((status = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        std::exit(1);
    }

    int sockkies = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sockkies == -1)
    {
        std::cout<<"error with getting socket descriptor\n";
        std::exit(1);
    }
    else
    {
        std::cout<<"socket descriptor is: " << sockkies << "\n";
    }

    //lose error to rebind to the same sock
    int yes=1;
    if (setsockopt(sockkies,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
        perror("setsockopt");
        exit(1);
    }
    //end of error removal

    int error = bind(sockkies, servinfo->ai_addr, servinfo->ai_addrlen);
    if( error == -1)
    {
        std::cout<<"error binding\n";
        std::exit(1);
    }
    else
    {
        std::cout<<"bound to a socket/port thingy\n";
    }

    error = listen(sockkies, 10);
    if (error == -1)
    {
        std::cout<<"error when trying to listen\n";
        std::exit(1);
    }
    else
    {
        std::cout<<"listening to the port\n";
    }
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    addr_size = sizeof(their_addr);

    std::vector<http::Worker> workers(worker_number);
    for(int i = 0; i < worker_number; i++)
    {
        workers.at(i).id = i + 1;
    }

    while(true)
    {
        int new_socket = accept(sockkies, (struct sockaddr *)&their_addr, &addr_size);
        if (new_socket != -1)
        {
            for(auto& worker : workers)
            {
                if (worker.isAvailable())
                {
                    worker.assign(new_socket);
                    break;
                }
            }
        }
    }
    freeaddrinfo(servinfo);
}
