#include "../declaration/Tcp_client.hpp"

#include <iostream>
#include <bits/ostream.tcc>

TCP_client::TCP_client() = default;

TCP_client::~TCP_client() = default;

void TCP_client::start() {
    int         sockfd;
    char        buffer[MAXLINE];
    const auto  hello = "Hello from client";
    sockaddr_in servaddr{};
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::perror("socket creation failed");
        std::exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    socklen_t len;
    sendto(sockfd, static_cast<const char *>(hello), strlen(hello), 1, reinterpret_cast<const sockaddr *>(&servaddr), sizeof(servaddr));
    std::cout << "Sent " << strlen(hello) << " bytes to client" << std::endl;
    std::cout << "Hello message sent." << std::endl;
    int size = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, reinterpret_cast<struct sockaddr *>(&servaddr), &len);
    std::cout << "Server :" + std::string(buffer) << std::endl;
    // close(sockfd);
    // return 0;
}

SocketStatus TCP_client::init_socket(std::string ip, int port) {
    int result = WSAStartup(MAKEWORD(2, 2), &_wsa_data_);
    if (result != 0) {
        return SocketStatus::err_socket_init;
    }
    _tcp_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_tcp_socket_ == INVALID_SOCKET) {
        WSACleanup();
        return SocketStatus::err_socket_init;
    }
    _server_addr_.sin_family      = AF_INET;
    _server_addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    _server_addr_.sin_port        = htons(port);
    result                        = connect(_tcp_socket_, (SOCKADDR *) &_server_addr_, sizeof(_server_addr_));
    if (result == SOCKET_ERROR) {
        result = closesocket(_tcp_socket_);
        WSACleanup();
        return SocketStatus::err_socket_connect;
    }
    return SocketStatus::connected;
}

bool TCP_client::handle() const {
    char recvbuf[32];
    auto res = send(_tcp_socket_, _message_, sizeof(_message_), 0);
    if (res < 0) {
        return false;
    }
    res = recv(_tcp_socket_, recvbuf, sizeof(recvbuf), 0);
    if (res < 0) {
        return false;
    }
    std::cout << recvbuf << std::endl;
    return true;
}
