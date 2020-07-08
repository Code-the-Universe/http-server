#include <SFML/Network.hpp>

int main()
{
    sf::TcpListener server;
    server.listen(80);
    while(true)
    {
        sf::TcpSocket client;
        server.accept(client);
        client.send("Hello, I am server!", 20);
    }
}