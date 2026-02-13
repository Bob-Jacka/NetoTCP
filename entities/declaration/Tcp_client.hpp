#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "../INet.hpp"

class TCP_client final : INet {
#ifdef _WIN32
    WSADATA _wsa_data_;
#endif // _WIN32
    SOCKET      _tcp_socket_  = INVALID_SOCKET;
    sockaddr_in _server_addr_ = {};
    char        _message_[18] = "Hello from client";

    public:
        TcpClent();

        ~TcpClent();

        SocketStatus init_socket(std::string ip, int port);

        bool handle() const;
};

#endif
