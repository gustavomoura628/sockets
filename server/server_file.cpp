#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "Server_Socket.hpp"
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char * argv[])
{
    char * filepath = argv[1];
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cout << "Could not open file [" << filepath << "]\n";
        return 1;
    }

    Server_Socket sock(8080);

    int connection = sock.accepts();

    // Echo input back to client
    char buffer[1024] = { 0 };
    while (true)
    {
        file.read(buffer, 1024);
        int valread = file.gcount();
        if ( valread == 0 ) break;
        send(connection, buffer, valread, 0);
    }

    file.close();

    // closing the connected socket
    close(connection);

    return 0;
}
