#include "../declaration/TCP_server.hpp"

#include <iostream>
#include <thread>

TCP_server::TCP_server() = default;

TCP_server::~TCP_server() = default;

void TCP_server::start() {
    int         sockfd;
    char        buffer[1024];
    const auto  hello = "Hello from server";
    sockaddr_in servaddr{}, cliaddr{};
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        std::exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);
    if (bind(sockfd, reinterpret_cast<const sockaddr *>(&servaddr), sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    socklen_t len = sizeof(cliaddr);
    int       n   = recvfrom(sockfd, buffer, 1024, MSG_WAITALL, reinterpret_cast<struct sockaddr *>(&cliaddr), &len);
    // libio::output::println("Client :" + std::string(buffer));
    sendto(sockfd, hello, strlen(hello), 1, reinterpret_cast<const sockaddr *>(&cliaddr), len);
    // libio::output::println("Hello message sent.");
    // return 0;
}

SocketStatus TCP_server::init_socket(int port) {
    int result = WSAStartup(MAKEWORD(2, 2), &_wsa_data_);
    if (result != 0) {
        return SocketStatus::err_socket_init;
    }
    _listen_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listen_socket_ == INVALID_SOCKET) {
        WSACleanup();
        return SocketStatus::err_socket_init;
    }
    _server_addr_.sin_family      = AF_INET;
    _server_addr_.sin_addr.s_addr = ADDR_ANY;
    _server_addr_.sin_port        = htons(port);

    int res_bind = bind(_listen_socket_, (SOCKADDR *) &_server_addr_, sizeof(_server_addr_));
    if (res_bind == SOCKET_ERROR) {
        res_bind = closesocket(_listen_socket_);
        WSACleanup();
        return SocketStatus::err_socket_bind;
    }
    if (listen(_listen_socket_, SOMAXCONN) == SOCKET_ERROR) {
        res_bind = closesocket(_listen_socket_);
        WSACleanup();
        return SocketStatus::err_socket_listen;
    }
    return SocketStatus::listening;
}

[[noreturn]] void TCP_server::run() {
    while (true) {
        int addrlen = sizeof(_client_addr_);
        if ((_client_socket_ = accept(_listen_socket_, (struct sockaddr *) &_client_addr_, &addrlen)) == INVALID_SOCKET) {
            closesocket(_listen_socket_);
            WSACleanup();
        }
        std::thread(&TCP_server::client_handler, this, &_client_socket_).detach();
    }
}

void TCP_server::client_handler(SOCKET *client_socket) {
    char recvbuf[1024];
    int  result = recv(*client_socket, recvbuf, sizeof(recvbuf), 0);
    if (result > 0) {
        std::cout << recvbuf << std::endl;
        send(*client_socket, _server_answer_, 16, 0);
    }
}
