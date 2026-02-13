#ifndef INET_HPP
#define INET_HPP

#ifdef WIN32
#pragma message("Using Windows Sockets")
#include <winsock2.h>
#include <ws2tcpip.h>
#elifdef LINUX
#pragma message("Using Linux Sockets")
#include <Сsys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include <cstdint>
#include <cstdlib>
#include <string>

#define PORT 8080
#define MAXLINE 1024

enum class SocketStatus : std::uint8_t {
    connected = 0,
    listening,
    err_socket_init,
    err_socket_bind,
    err_socket_connect,
    err_socket_listen,
    disconnected
};

class INet {
    public:
        INet();

        virtual ~INet() = 0;

        virtual void start() = 0;
};

#endif
