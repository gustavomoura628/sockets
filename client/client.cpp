#include "Client_Socket.hpp"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char const* argv[])
{
    Client_Socket sock("127.0.0.1", 8080);

    std::cout << "Write message: ";
    char buffer[1024] = { 0 };
    std::cin.getline(buffer,1024);

    sock.sends(buffer, strlen(buffer), 0);

    int valread = sock.reads(buffer, 1024);

    printf("%s\n", buffer);
    return 0;
}
