#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include "../../config.h"

constexpr int NO_FLAGS = 0;

class Server
{
public:
    /**
     * @brief this function starts the listening of the server
     * 
     * @param port the server's port
     */
    static void StartListening(uint32_t port);

    /**
     * @brief function handles work with single client
     * 
     * @param socketFd the socket which the client is connected
     */
    static void HandleClient(int socketFd);    
};
