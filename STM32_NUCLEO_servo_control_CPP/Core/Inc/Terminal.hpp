#ifndef INC_TERMINAL_HPP_
#define INC_TERMINAL_HPP_

#include "main.h"
#include <cstdlib> // For atoi
#include <cstring>

class Terminal {
private:
    UART_HandleTypeDef* _huart;
    char _buffer[10];
    uint8_t _index;

public:
    Terminal(UART_HandleTypeDef* huart);

    int scanAngle();

    // Helper to send text easily
    void print(const char* msg);
    // Upgraded version of print for debugging
    void printf(const char* format, ...);
};


#endif /* INC_TERMINAL_HPP_ */
