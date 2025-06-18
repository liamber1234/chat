#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>

#include "EStatusCode.h"
#include "../config.h"

constexpr char* LOOP_BACK_IP = "127.0.0.1";

class Client
{
public:
    // C'tor
    Client();

    /**
     * @brief function handles client work - enabling the client connect the server and send messages
     * 
     * @param ip the server's ip
     * @param port the server's port
     * 
     * @return status code which represents the result of the function
     */
    EStatusCode Run(char* ip, uint8_t ip_length, uint16_t port);

private:
    /**
     * @brief function is connecting to server with the given parameters
     * 
     * @param ip the server's ip
     * @param port the server's port
     * 
     * @return EStatusCode which represents the function result
     */
    EStatusCode ConnectToServer(char* ip, uint16_t port);

    /**
     * @brief function gets input from the user 
     * 
     * @param buffer to set the input to 
     * @param o_length out parameter which the buffer length will be saved in 
     */
    void GetInput(char* buffer, size_t& o_length);

    /**
     * @brief function receives messages from the server
     * 
     * @param socket_fd the file descriptor of the socket
     */
    void ReceiveMessages(fd_t socket_fd);


    fd_t socket_fd;
};

#endif // CLIENT_H