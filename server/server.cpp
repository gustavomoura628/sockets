#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "Server_Socket.hpp"

int main(int argc, char * argv[])
{
    Server_Socket sock(8080);

    int connection = sock.accepts();

    // Echo input back to client
    char buffer[1024] = { 0 };
    while (true)
    {
        int valread = read(connection, buffer, 1024);
        char prompt[1024] = "Clacks response: ";
        strcat(prompt,buffer);
        strcpy(buffer,prompt);

        if ( valread == 0 ) break;
        printf("%s\n", buffer);
        send(connection, buffer, strlen(buffer), 0);
    }

    // closing the connected socket
    close(connection);

    return 0;
}
