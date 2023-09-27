#include "Client_Socket.hpp"
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
void Client_Socket::creates()
{
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }
}

// Gets adress struct from adress string (i.e. 127.0.0.1)
void Client_Socket::get_server_address(const char *__restrict address_string)
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, address_string, &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
}

void Client_Socket::connects()
{
    int status;
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
}

Client_Socket::Client_Socket(const char *__restrict adress_string, int _port)
{
    port = _port;
    creates();
    get_server_address(adress_string);
    connects();
}
Client_Socket::~Client_Socket()
{
    closes();
}
int Client_Socket::sends(const void * buffer, size_t n, int flags)
{
    return send(client_fd, buffer, n, flags);
}

int Client_Socket::reads(void *buf, size_t nbytes)
{
    return read(client_fd, buf, nbytes);
}

void Client_Socket::closes()
{
    // closing the connected socket
    close(client_fd);
}
