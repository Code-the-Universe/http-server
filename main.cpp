#include <SFML/Network.hpp>
#include <iostream>

int main()
{
    sf::TcpListener server;
    server.listen(6669);
    while(true)
    {
        sf::TcpSocket client;
        server.accept(client);
        std::cout << "Connection received!" << std::endl;
        std::string data = "HTTP/1.1 501 Not Implemented";
        client.send(data.data(), data.size() + 1);
    }
}