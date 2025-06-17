#include "Client.h"
#include "Server.h"
#include "../config.h"

int main(void) {
    char side;
    Client c = Client();
    printf("enter the side you want to open: S for server and C for client:\n");
    scanf("%c", &side);
    switch (side)
    {
    case 'C':
        c.Run(LOOP_BACK_IP, strlen(LOOP_BACK_IP), CONFIG_PORT);
        break;
    case 'S':
        Server::StartListening(CONFIG_PORT);
    default:
        break;
    }

}