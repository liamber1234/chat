#include <stdio.h>
#include "EStatusCode.h"
#include <stdint.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

constexpr char* LOOP_BACK_IP = "127.0.0.1";
constexpr int NO_FLAGS = 0;

class Client
{
public:
    //C'tor
    Client();

    /**
     * @brief function handles client work - enabling the client connect the server and send messages
     * 
     * @param IP the server's ip
     * @param port the server's port
     */
    void HandleClient(char* IP, uint16_t port);

private:
    /**
     * @brief function is connecting to server with the given parameters
     * 
     * @param IP the server's ip
     * @param port the server's port
     * 
     * @return EStatusCode which represents the function result
     */
    EStatusCode ConnectToServer(char* IP, uint16_t port);

    /**
     * @brief function is sending data to server and check server's answer
     * 
     * @return EStatusCode which represents the function result
     */
    EStatusCode ReceiveSendedData();

private:
    int socket_fd;
};