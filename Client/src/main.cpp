#include "Client.h"
#include "../../config.h"

int main(void) {
    Client c = Client();
    c.Run(LOOP_BACK_IP, strlen(LOOP_BACK_IP), CONFIG_PORT);
}