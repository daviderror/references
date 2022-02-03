cmake_minimum_required(VERSION 3.0)

project(udp_server)

include_directories(inc/)

add_executable(udp_server 
    src/main.cpp 
    src/udp_server.cpp 
    src/udp.cpp
)

install(TARGETS udp_server RUNTIME DESTINATION bin)
