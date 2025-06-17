#include "Client.h"
#include "../config.h"

Client::Client() : socket_fd(0) {}

EStatusCode Client::Run(char* ip, uint8_t ip_length, uint16_t port)
{
    size_t buffer_length = 0;
    char sended_buffer[MAX_BUFFER_SIZE] = {0};
    char changed_ip[ip_length] = {0}; 
    if (ip == nullptr)
    {
        return EStatusCode::NullPointer;
    }
    EStatusCode state;
    changed_ip[ip_length - 1] = '\0';

    state = this->ConnectToServer(ip, port);
    if (state != EStatusCode::Success)
    {
        return state;
    }
    std::thread inner_thread = std::thread(&Client::ReceiveMessages, this, socket_fd);
    inner_thread.detach();
    while (true) 
    {
        GetInput(sended_buffer, buffer_length);
        if (send(socket_fd, sended_buffer, MAX_BUFFER_SIZE, NO_FLAGS) == -1)
        {
            break;
        }
        sleep(0.05); // set delay to make the thread print my message before trying to send the next message
    }
    
}

EStatusCode Client::ConnectToServer(char* ip, uint16_t port)
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        return EStatusCode::SocketCreationError;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
    {
        return EStatusCode::InvalidParameters;
    }

    if (connect(socket_fd,reinterpret_cast<struct sockaddr *>(&serv_addr), sizeof(serv_addr)) < 0)
    {
        return EStatusCode::SocketCreationError;
    }
    
    return EStatusCode::Success;
}

void Client::GetInput(char* buffer, size_t& o_length)
{
    printf("Enter message to send\n");
    scanf("%s", buffer);
    o_length = strlen(buffer);
}

void Client::ReceiveMessages(fd_t socket_fd)
{
    std::mutex mtx;
    char received_buffer[MAX_BUFFER_SIZE] = {0};
    while (recv(socket_fd, received_buffer, MAX_BUFFER_SIZE, NO_FLAGS) != SOCKET_ERROR)
    {
        mtx.lock();
        printf("%s\n", received_buffer);
        memset(received_buffer, '\0', strlen(received_buffer));
        mtx.unlock();
    }
}