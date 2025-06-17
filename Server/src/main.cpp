#include <stdio.h>
#include "Server.h"

int main(void) {
    Server::StartListening(CONFIG_PORT);
}