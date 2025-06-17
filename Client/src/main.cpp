#include "Client.h"
#include "../../config.h"

int main(void) {
    Client *c = new Client();
    c->HandleClient(LOOP_BACK_IP, CONFIG_PORT);
}

