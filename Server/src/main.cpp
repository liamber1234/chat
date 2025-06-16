#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

constexpr int NO_FLAGS = 0;

int main(void) {
    printf("hello");
}

/**
 * @brief this function starts the listening of the server
 * 
 * @param port the server's port
 */
void StartListening(uint32_t port)
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
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

/**
 * @brief function handles work with single client
 * 
 * @param socketFd the socket which the client is connected
 */
void HandleClient(int socketFd)
{
    int clientSocket = accept(socketFd, nullptr, nullptr);
    char buffer[1024] = { 0 };

    while (recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT) != 0)
    {
        send(socketFd, buffer, sizeof(buffer), NO_FLAGS);
    }
}

