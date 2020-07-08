#include <SFML/Network.hpp>
#include <iostream>
int main()
{
    std::cout<<"starting\n";
    sf::TcpListener socket;
    if (socket.listen(80) != sf::Socket::Done)
    {
        std::cout<<"error binding\n";
    }
    sf::SocketSelector selector;
    selector.add(socket);
    while(true)
    {
        if (selector.wait(sf::seconds(10.f)))
        {
            if (selector.isReady(socket))
            {
                sf::TcpSocket client;
                if (socket.accept(client) == sf::Socket::Done)
                {
                    std::cout<<"clinu accepted\n";
                    char data[10000];
                    size_t received;
                    if( client.receive(data, 10000, received) == sf::Socket::Done)
                    {
                        std::cout<<data<<"\n";
                        if ( client.send("HTTP/1.1 200 OK\nHello\n", 22) != sf::Socket::Done)
                        {
                            std::cout<<"error sending to cli\n";
                        }
                    }
                }
            }
        }
    }
}
