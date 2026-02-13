#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../INet.hpp"

class TCP_server final : INet {
    WSADATA     _wsa_data_      = {};
    SOCKET      _listen_socket_ = INVALID_SOCKET;
    sockaddr_in _server_addr_   = {};
    sockaddr_in _client_addr_   = {};
    SOCKET      _client_socket_;
    char        server_answer[16] = "Server Answer!!";

    public:
        TCP_server();

        ~TCP_server();

        SocketStatus init_socket(int port);

        void run();

        void client_handler(SOCKET *client_socket);
};

};

#endif
