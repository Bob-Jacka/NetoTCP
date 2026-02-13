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
