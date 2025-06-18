#include "Server.h"

Server::Server() {}

void Server::StartListening(uint16_t port)
{
    std::mutex mtx;
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
    if(listen(serverSocket, MAX_USERS_AMOUNT) != 0)
    {
        return;
    }
    while (true)
    {
        fd_t clientSocket = accept(serverSocket, nullptr, nullptr);
        mtx.lock();
        for (size_t i = 0; i < MAX_USERS_AMOUNT; i++)
        {
            if (!m_all_sockets[i].has_value())
            {
                m_all_sockets[i] = clientSocket;
                break;
            }
        }
        mtx.unlock();

        std::thread client_thread = std::thread(&Server::HandleClient, this, clientSocket);
        client_thread.detach();
    }
}

void Server::HandleClient(fd_t clientSocket)
{
    char buffer[MAX_BUFFER_SIZE] = { 0 };
    ssize_t read_bytes = 0;

    while (read_bytes = recv(clientSocket, buffer, MAX_BUFFER_SIZE, NO_FLAGS) > 0)
    {
        printf("%s", buffer);
        SendMessageToEveryone(buffer, strlen(buffer));
    }
    DeleteSocket(clientSocket);
    
}

bool Server::DeleteSocket(fd_t socket_fd)
{
    for (size_t i = 0; i < MAX_USERS_AMOUNT; i++)
    {
        if (m_all_sockets[i].value() == socket_fd)
        {
            m_all_sockets[i] = std::nullopt;
            return true;
        }
    }
    return false;
}

void Server::SendMessageToEveryone(char* message, size_t message_length)
{
    for (size_t i = 0; i < MAX_USERS_AMOUNT; i++)
    {
        if (m_all_sockets[i].has_value())
        {
            send(m_all_sockets[i].value(), message, message_length, NO_FLAGS);
        }
    }
}