cmake_minimum_required(VERSION 3.31)
project(NetoTCP)

set(CMAKE_CXX_STANDARD 23)

add_executable(NetoTCP
        firstTask/main.cpp
#        secondTask/main.cpp

#        entities/declaration/Tcp_client.hpp
        entities/declaration/TCP_server.hpp

        entities/realization/TCP_server.cpp
#        entities/realization/Tcp_client.cpp
        entities/INet.hpp

#        libio.cppm
)

#target_sources(NetoTCP
#        PUBLIC
#        FILE_SET all_my_modules TYPE CXX_MODULES FILES
#        libio.cppm
#)
