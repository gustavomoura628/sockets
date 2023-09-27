#ifndef _SERVER_SOCKET_HPP
#define _SERVER_SOCKET_HPP
#include <netinet/in.h>

class Server_Socket{
    private:
        int server_fd;
        struct sockaddr_in address;
        unsigned int port = 8080;
        int opt = 1;

        void creates();
        void binds();
        void listens();

    public:
        Server_Socket(int _port);
        ~Server_Socket();
        int accepts();
        void shutdowns();
};
#endif
