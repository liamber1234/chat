#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <string.h>
#include <pthread.h>

#include "../config.h"

using fd_t = int;

class Server
{
public:
    // C'tor
    Server();

    /**
     * @brief this function starts the listening of the server
     * 
     * @param port the server's port
     */
    void StartListening(uint16_t port);

    /**
     * @brief function handles work with single client
     * 
     * @param socketFd the socket which the client is connected
     */
    void HandleClient(fd_t socketFd);    

    /**
     * @brief funtion removes socket from the lists
     * 
     * @param socket_fd the file descriptor of the socket
     * 
     * @return true if operation has been succeeded, false otherwise
     */
    bool DeleteSocket(fd_t socket_fd);

    /**
     * @brief funtion sends message to everyone in the list
     * 
     * @param message the message content
     * @param message_length the length of the message
     */
    void SendMessageToEveryone(char* message, size_t message_length);

private:
    fd_t m_all_sockets[MAX_USERS_AMOUNT];
    bool m_used_sockets[MAX_USERS_AMOUNT];
};

#endif // SERVER_H