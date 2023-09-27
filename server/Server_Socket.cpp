#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Server_Socket.hpp"


void Server_Socket::creates()
{
    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( server_fd < 0 )
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

void Server_Socket::binds()
{
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Server_Socket::listens()
{
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

Server_Socket::Server_Socket(int _port)
{
    port = _port;
    creates();
    binds();
    listens();
}

Server_Socket::~Server_Socket()
{
    shutdowns();
}


int Server_Socket::accepts()
{
    int connection;
    int addrlen = sizeof(address);
    if ((connection
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return connection;
}

void Server_Socket::shutdowns()
{
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
}
