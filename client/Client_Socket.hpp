#ifndef _CLIENT_SOCKET_HPP
#define _CLIENT_SOCKET_HPP
#include <arpa/inet.h>
  
class Client_Socket{
    private:
        int client_fd;
        struct sockaddr_in serv_addr;
        int port;
        void creates();
        // Gets adress struct from adress string (i.e. 127.0.0.1)
        void get_server_address(const char *__restrict address_string);
        void connects();

    public:
        Client_Socket(const char *__restrict adress_string, int _port);
        ~Client_Socket();
        int sends(const void * buffer, size_t n, int flags);
        int reads(void *buf, size_t nbytes);
        void closes();
};
#endif
