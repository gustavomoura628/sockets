#include "Client_Socket.hpp"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

int main(int argc, char * argv[])
{
    char * filepath = argv[1];
    std::ofstream file(filepath);
    if (!file.is_open())
    {
        std::cout << "Could not open file [" << filepath << "]\n";
        return 1;
    }

    Client_Socket sock("127.0.0.1", 8080);

    char buffer[1024] = { 0 };

    while(true)
    {
        int valread = sock.reads(buffer, 1024);
        if(valread == 0) break;
        file.write(buffer, valread);
    }

    file.close();

    return 0;
}
