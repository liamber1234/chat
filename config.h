#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

constexpr uint32_t CONFIG_PORT = 55124;
constexpr uint16_t MAX_BUFFER_SIZE = 2048;
constexpr int NO_FLAGS = 0;
constexpr size_t MAX_USERS_AMOUNT = 5;
constexpr ssize_t SOCKET_ERROR = -1;

#endif // CONFIG_H