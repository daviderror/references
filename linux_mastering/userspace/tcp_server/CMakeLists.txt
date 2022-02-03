cmake_minimum_required(VERSION 3.0)

project(tcp_server)

include_directories(inc/)

add_executable(tcp_server 
    src/main.cpp 
    src/tcp_server.cpp 
    src/tcp.cpp
)

install(TARGETS tcp_server RUNTIME DESTINATION bin)
