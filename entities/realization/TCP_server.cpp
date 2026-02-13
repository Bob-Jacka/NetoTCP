#include "../declaration/TCP_server.hpp"

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
