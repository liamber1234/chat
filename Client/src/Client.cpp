#include "Client.h"
#include "../../config.h"

Client::Client() : socket_fd(0) {}

void Client::HandleClient(char* IP, uint16_t port)
{
    this->ConnectToServer(IP, port);

    //while (ReceiveSendedData() == EStatusCode::Success) {}
    
}

EStatusCode Client::ConnectToServer(char* IP, uint16_t port)
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        return EStatusCode::SocketCreationError;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0)
    {
        return EStatusCode::InvalidParameters;
    }

    if (connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        return EStatusCode::SocketCreationError;
    }

    while (ReceiveSendedData() == EStatusCode::Success) { }
    
    return EStatusCode::Success;
}

EStatusCode Client::ReceiveSendedData()
{
    char sended_buffer[MAX_BUFFER_SIZE] = {0};
    char received_buffer[MAX_BUFFER_SIZE] = {0};
    printf("Enter message to send");
    scanf("%s", sended_buffer);
    send(socket_fd, sended_buffer, MAX_BUFFER_SIZE, NO_FLAGS);
    recv(socket_fd, received_buffer, MAX_BUFFER_SIZE, NO_FLAGS);
    printf("%s", received_buffer);
    if (memcmp(sended_buffer, received_buffer, 3) != 0)
    {
        printf("Bad");
        return EStatusCode::SocketClosed;
    }
    return EStatusCode::Success;
    
}