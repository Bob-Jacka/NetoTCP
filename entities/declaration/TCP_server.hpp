#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../INet.hpp"

class TCP_server final : INet {
    public:
        TCP_server();

        ~TCP_server() override;

        void start() override;
};

#endif
