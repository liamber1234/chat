#include "Server.h"

void Server::StartListening(uint32_t port)
{
    printf("hereee");
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
        
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    while (true)
    {
        if(listen(serverSocket, 1) == 0)
        {
            HandleClient(serverSocket);
        }
    }
}

void Server::HandleClient(int socketFd)
{
    int clientSocket = accept(socketFd, nullptr, nullptr);
    char buffer[1024] = { 0 };

    while (recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT) != 0)
    {
        send(socketFd, buffer, sizeof(buffer), NO_FLAGS);
    }
}