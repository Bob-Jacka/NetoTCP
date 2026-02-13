#include "../entities/declaration/TCP_server.hpp"

int main() {
    const auto serv = new TCP_server();
    serv->start();
}
