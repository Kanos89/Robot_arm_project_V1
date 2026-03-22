#include "Terminal.hpp"
#include <cstdarg>  // This defines va_list, va_start, va_end
#include <cstdio>
#include <cstring>

Terminal::Terminal(UART_HandleTypeDef* huart) : _huart(huart), _index(0) {
    memset(_buffer, 0, sizeof(_buffer));
}

void Terminal::print(const char* msg) {
    HAL_UART_Transmit(_huart, (uint8_t*)msg, strlen(msg), 100);
}

void Terminal::printf(const char* format, ...) { // Comes for debugging
    char temp_buffer[128]; // Enough for a long debug line
    va_list args;
    va_start(args, format);

    // This function does the "magic" of turning %d or %s into actual text
    vsnprintf(temp_buffer, sizeof(temp_buffer), format, args);

    va_end(args);

    print(temp_buffer);
}

int Terminal::scanAngle() {
    _index = 0;
    memset(_buffer, 0, sizeof(_buffer));
    uint8_t char_in;

    while (_index < 9) {
        if (HAL_UART_Receive(_huart, &char_in, 1, HAL_MAX_DELAY) == HAL_OK) {
            // Handle Enter key
            if (char_in == '\r' || char_in == '\n') {
                print("\r\n");
                break;
            }
            // Handle Backspace
            else if (char_in == 8 || char_in == 127) {
                if (_index > 0) {
                    _index--;
                    _buffer[_index] = 0;
                    print("\b \b");
                }
            }
            // Handle Numbers only (Filtering)
            else if (char_in >= '0' && char_in <= '9') {
                _buffer[_index++] = char_in;
                HAL_UART_Transmit(_huart, &char_in, 1, 10);
            }
        }
    }
    return atoi(_buffer);
}
