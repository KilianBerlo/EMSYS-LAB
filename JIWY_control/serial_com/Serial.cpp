//
// Created by glen on 07-06-21.
//

#include <termios.h>
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <termio.h>
#include <vector>
#include <cstring>

#include "Serial.h"

Serial::Serial(std::string com_port)
{
    file = open(com_port.c_str(), O_RDWR);
    if (file == -1) {
        perror(com_port.c_str());
        return;
    }

    struct termios tios;
    tcgetattr(file, &tios);
// disable flow control and all that, and ignore break and parity errors
    tios.c_iflag = IGNBRK | IGNPAR;
    tios.c_oflag = 0;
    tios.c_lflag = 0;
    cfsetspeed(&tios, B115200);
    tcsetattr(file, TCSAFLUSH, &tios);

// the serial port has a brief glitch once we turn it on which generates a
// start bit; sleep for 1ms to let it settle
    usleep(1000);
}

void Serial::write_array(std::array<uint8_t, 4> data)
{
    if (file != -1)
    {
        if (write(file, data.data(), data.size()) == -1)
        {
            std::cout << "Sending to COM port failed.." << std::endl;
        }
    }
}

std::optional<Serial::rx_message> Serial::readMessage(bool await_response)
{
    // Temporary data array.
    std::array<uint8_t ,MESSAGE_SIZE> temp{};

    if (await_response)
    {
        if (file != -1)
        {
            read(file, temp.data(), MESSAGE_SIZE);

            Serial::rx_message received_message{};
            std::memcpy(&received_message, &temp, MESSAGE_SIZE);

            return received_message;
        }
    }
    else
    {
        int available;
        if( ioctl( file, FIONREAD, &available ) < 0 ) {
            // Error handling here
        }

        if (file != -1 && available > 0)
        {
            read(file, temp.data(), MESSAGE_SIZE);

            Serial::rx_message received_message{};
            std::memcpy(&received_message, &temp, MESSAGE_SIZE);

            return received_message;
        }
    }

    return std::nullopt;
}
