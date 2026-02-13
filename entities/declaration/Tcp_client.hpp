#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "../INet.hpp"

class TCP_client final : INet {
    public:
        TCP_client();

        ~TCP_client() override;

        void start() override;
};

#endif
