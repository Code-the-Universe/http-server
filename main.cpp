#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>

int main()
{
    constexpr unsigned short port = 27277;
    sf::TcpListener listener{ };
    auto result = listener.listen(port);
    if(result != sf::Socket::Done)
    {
        std::cout << "Error binding!\n";
        std::exit(1);
    }
    while(true)
    {
        sf::TcpSocket client;
        result = listener.accept(client);
        if (result != sf::Socket::Done) {
            std::cout << "Error accepting client! \n";
            std::exit(1);
        } else {
            std::cout << "Accepted client! \n";
        }
        std::string HTTP = "HTTP/1.1 501 NOT IMPLEMENTED \nDate: ";
        std::time_t time = std::time(nullptr);
        HTTP += std::asctime(std::localtime(&time));
        std::size_t sent;
        client.send(HTTP.c_str(), HTTP.size() + 1, sent);
        std::cout << "Sent " << sent << " characters:\n" << HTTP;
    }
}