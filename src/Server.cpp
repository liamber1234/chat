#include "Server.h"

void Server::StartListening(uint16_t port)
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) 
    {
        printf("failed");
        return;
    }
    if(listen(serverSocket, 1) != 0)
    {
        return;
    }
    while (true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        HandleClient(clientSocket);
    }
}

void Server::HandleClient(int clientSocket)
{
    char buffer[MAX_BUFFER_SIZE] = { 0 };
    ssize_t read_bytes = 0;

    while (read_bytes = recv(clientSocket, buffer, MAX_BUFFER_SIZE, NO_FLAGS) > 0)
    {
        printf("%s", buffer);
        ssize_t bytesSent = send(clientSocket, buffer, MAX_BUFFER_SIZE, 0);
    }
}